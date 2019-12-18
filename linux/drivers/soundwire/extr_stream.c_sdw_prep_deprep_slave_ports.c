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
typedef  int /*<<< orphan*/  u32 ;
struct sdw_slave_runtime {TYPE_2__* slave; int /*<<< orphan*/  direction; } ;
struct sdw_prepare_ch {size_t num; int ch_mask; int prepare; int /*<<< orphan*/  bank; } ;
struct sdw_port_runtime {size_t num; int ch_mask; } ;
struct sdw_dpn_prop {scalar_t__ imp_def_interrupts; int /*<<< orphan*/  ch_prep_timeout; int /*<<< orphan*/  simple_ch_prep_sm; } ;
struct TYPE_6__ {int /*<<< orphan*/  next_bank; } ;
struct sdw_bus {TYPE_1__ params; int /*<<< orphan*/ * dev; } ;
struct completion {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; struct completion* port_ready; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SDW_DPN_PREPARECTRL (size_t) ; 
 int /*<<< orphan*/  SDW_DPN_PREPARESTATUS (size_t) ; 
 int /*<<< orphan*/  SDW_OPS_PORT_POST_PREP ; 
 int /*<<< orphan*/  SDW_OPS_PORT_PRE_PREP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int sdw_configure_dpn_intr (TYPE_2__*,size_t,int,scalar_t__) ; 
 int /*<<< orphan*/  sdw_do_port_prep (struct sdw_slave_runtime*,struct sdw_prepare_ch,int /*<<< orphan*/ ) ; 
 struct sdw_dpn_prop* sdw_get_slave_dpn_prop (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int sdw_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int sdw_update (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 unsigned int wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdw_prep_deprep_slave_ports(struct sdw_bus *bus,
				       struct sdw_slave_runtime *s_rt,
				       struct sdw_port_runtime *p_rt,
				       bool prep)
{
	struct completion *port_ready;
	struct sdw_dpn_prop *dpn_prop;
	struct sdw_prepare_ch prep_ch;
	unsigned int time_left;
	bool intr = false;
	int ret = 0, val;
	u32 addr;

	prep_ch.num = p_rt->num;
	prep_ch.ch_mask = p_rt->ch_mask;

	dpn_prop = sdw_get_slave_dpn_prop(s_rt->slave,
					  s_rt->direction,
					  prep_ch.num);
	if (!dpn_prop) {
		dev_err(bus->dev,
			"Slave Port:%d properties not found\n", prep_ch.num);
		return -EINVAL;
	}

	prep_ch.prepare = prep;

	prep_ch.bank = bus->params.next_bank;

	if (dpn_prop->imp_def_interrupts || !dpn_prop->simple_ch_prep_sm)
		intr = true;

	/*
	 * Enable interrupt before Port prepare.
	 * For Port de-prepare, it is assumed that port
	 * was prepared earlier
	 */
	if (prep && intr) {
		ret = sdw_configure_dpn_intr(s_rt->slave, p_rt->num, prep,
					     dpn_prop->imp_def_interrupts);
		if (ret < 0)
			return ret;
	}

	/* Inform slave about the impending port prepare */
	sdw_do_port_prep(s_rt, prep_ch, SDW_OPS_PORT_PRE_PREP);

	/* Prepare Slave port implementing CP_SM */
	if (!dpn_prop->simple_ch_prep_sm) {
		addr = SDW_DPN_PREPARECTRL(p_rt->num);

		if (prep)
			ret = sdw_update(s_rt->slave, addr,
					 0xFF, p_rt->ch_mask);
		else
			ret = sdw_update(s_rt->slave, addr, 0xFF, 0x0);

		if (ret < 0) {
			dev_err(&s_rt->slave->dev,
				"Slave prep_ctrl reg write failed\n");
			return ret;
		}

		/* Wait for completion on port ready */
		port_ready = &s_rt->slave->port_ready[prep_ch.num];
		time_left = wait_for_completion_timeout(port_ready,
				msecs_to_jiffies(dpn_prop->ch_prep_timeout));

		val = sdw_read(s_rt->slave, SDW_DPN_PREPARESTATUS(p_rt->num));
		val &= p_rt->ch_mask;
		if (!time_left || val) {
			dev_err(&s_rt->slave->dev,
				"Chn prep failed for port:%d\n", prep_ch.num);
			return -ETIMEDOUT;
		}
	}

	/* Inform slaves about ports prepared */
	sdw_do_port_prep(s_rt, prep_ch, SDW_OPS_PORT_POST_PREP);

	/* Disable interrupt after Port de-prepare */
	if (!prep && intr)
		ret = sdw_configure_dpn_intr(s_rt->slave, p_rt->num, prep,
					     dpn_prop->imp_def_interrupts);

	return ret;
}