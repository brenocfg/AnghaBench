#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdw_transport_params {int sample_interval; int offset1; int blk_grp_ctrl; int lane_ctrl; int /*<<< orphan*/  port_num; scalar_t__ blk_grp_ctrl_valid; } ;
struct sdw_slave_runtime {TYPE_2__* slave; int /*<<< orphan*/  direction; } ;
struct sdw_slave_prop {scalar_t__ lane_control_support; } ;
struct sdw_port_params {int data_mode; int flow_mode; int bps; } ;
struct sdw_port_runtime {struct sdw_port_params port_params; struct sdw_transport_params transport_params; } ;
struct sdw_dpn_prop {scalar_t__ type; } ;
struct TYPE_6__ {scalar_t__ next_bank; } ;
struct sdw_bus {TYPE_1__ params; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; struct sdw_slave_prop prop; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SDW_DPN_BLOCKCTRL1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_BLOCKCTRL2_B0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_BLOCKCTRL2_B1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_LANECTRL_B0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_LANECTRL_B1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_OFFSETCTRL1_B0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_OFFSETCTRL1_B1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_PORTCTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_PORTCTRL_DATAMODE ; 
 int /*<<< orphan*/  SDW_DPN_SAMPLECTRL1_B0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_SAMPLECTRL1_B1 (int /*<<< orphan*/ ) ; 
 int SDW_DPN_SAMPLECTRL_LOW ; 
 scalar_t__ SDW_DPN_SIMPLE ; 
 int SDW_REG_SHIFT (int /*<<< orphan*/ ) ; 
 int _sdw_program_slave_port_params (struct sdw_bus*,TYPE_2__*,struct sdw_transport_params*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct sdw_dpn_prop* sdw_get_slave_dpn_prop (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdw_update (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int sdw_write (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sdw_program_slave_port_params(struct sdw_bus *bus,
					 struct sdw_slave_runtime *s_rt,
					 struct sdw_port_runtime *p_rt)
{
	struct sdw_transport_params *t_params = &p_rt->transport_params;
	struct sdw_port_params *p_params = &p_rt->port_params;
	struct sdw_slave_prop *slave_prop = &s_rt->slave->prop;
	u32 addr1, addr2, addr3, addr4, addr5, addr6;
	struct sdw_dpn_prop *dpn_prop;
	int ret;
	u8 wbuf;

	dpn_prop = sdw_get_slave_dpn_prop(s_rt->slave,
					  s_rt->direction,
					  t_params->port_num);
	if (!dpn_prop)
		return -EINVAL;

	addr1 = SDW_DPN_PORTCTRL(t_params->port_num);
	addr2 = SDW_DPN_BLOCKCTRL1(t_params->port_num);

	if (bus->params.next_bank) {
		addr3 = SDW_DPN_SAMPLECTRL1_B1(t_params->port_num);
		addr4 = SDW_DPN_OFFSETCTRL1_B1(t_params->port_num);
		addr5 = SDW_DPN_BLOCKCTRL2_B1(t_params->port_num);
		addr6 = SDW_DPN_LANECTRL_B1(t_params->port_num);

	} else {
		addr3 = SDW_DPN_SAMPLECTRL1_B0(t_params->port_num);
		addr4 = SDW_DPN_OFFSETCTRL1_B0(t_params->port_num);
		addr5 = SDW_DPN_BLOCKCTRL2_B0(t_params->port_num);
		addr6 = SDW_DPN_LANECTRL_B0(t_params->port_num);
	}

	/* Program DPN_PortCtrl register */
	wbuf = p_params->data_mode << SDW_REG_SHIFT(SDW_DPN_PORTCTRL_DATAMODE);
	wbuf |= p_params->flow_mode;

	ret = sdw_update(s_rt->slave, addr1, 0xF, wbuf);
	if (ret < 0) {
		dev_err(&s_rt->slave->dev,
			"DPN_PortCtrl register write failed for port %d\n",
			t_params->port_num);
		return ret;
	}

	/* Program DPN_BlockCtrl1 register */
	ret = sdw_write(s_rt->slave, addr2, (p_params->bps - 1));
	if (ret < 0) {
		dev_err(&s_rt->slave->dev,
			"DPN_BlockCtrl1 register write failed for port %d\n",
			t_params->port_num);
		return ret;
	}

	/* Program DPN_SampleCtrl1 register */
	wbuf = (t_params->sample_interval - 1) & SDW_DPN_SAMPLECTRL_LOW;
	ret = sdw_write(s_rt->slave, addr3, wbuf);
	if (ret < 0) {
		dev_err(&s_rt->slave->dev,
			"DPN_SampleCtrl1 register write failed for port %d\n",
			t_params->port_num);
		return ret;
	}

	/* Program DPN_OffsetCtrl1 registers */
	ret = sdw_write(s_rt->slave, addr4, t_params->offset1);
	if (ret < 0) {
		dev_err(&s_rt->slave->dev,
			"DPN_OffsetCtrl1 register write failed for port %d\n",
			t_params->port_num);
		return ret;
	}

	/* Program DPN_BlockCtrl2 register*/
	if (t_params->blk_grp_ctrl_valid) {
		ret = sdw_write(s_rt->slave, addr5, t_params->blk_grp_ctrl);
		if (ret < 0) {
			dev_err(&s_rt->slave->dev,
				"DPN_BlockCtrl2 reg write failed for port %d\n",
				t_params->port_num);
			return ret;
		}
	}

	/* program DPN_LaneCtrl register */
	if (slave_prop->lane_control_support) {
		ret = sdw_write(s_rt->slave, addr6, t_params->lane_ctrl);
		if (ret < 0) {
			dev_err(&s_rt->slave->dev,
				"DPN_LaneCtrl register write failed for port %d\n",
				t_params->port_num);
			return ret;
		}
	}

	if (dpn_prop->type != SDW_DPN_SIMPLE) {
		ret = _sdw_program_slave_port_params(bus, s_rt->slave,
						     t_params, dpn_prop->type);
		if (ret < 0)
			dev_err(&s_rt->slave->dev,
				"Transport reg write failed for port: %d\n",
				t_params->port_num);
	}

	return ret;
}