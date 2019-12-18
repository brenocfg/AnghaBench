#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sdw_transport_params {int /*<<< orphan*/  port_num; } ;
struct sdw_slave_runtime {TYPE_2__* slave; } ;
struct sdw_port_runtime {int ch_mask; int /*<<< orphan*/  num; struct sdw_transport_params transport_params; } ;
struct TYPE_3__ {scalar_t__ next_bank; } ;
struct sdw_bus {TYPE_1__ params; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDW_DPN_CHANNELEN_B0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDW_DPN_CHANNELEN_B1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sdw_update (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sdw_enable_disable_slave_ports(struct sdw_bus *bus,
					  struct sdw_slave_runtime *s_rt,
					  struct sdw_port_runtime *p_rt,
					  bool en)
{
	struct sdw_transport_params *t_params = &p_rt->transport_params;
	u32 addr;
	int ret;

	if (bus->params.next_bank)
		addr = SDW_DPN_CHANNELEN_B1(p_rt->num);
	else
		addr = SDW_DPN_CHANNELEN_B0(p_rt->num);

	/*
	 * Since bus doesn't support sharing a port across two streams,
	 * it is safe to reset this register
	 */
	if (en)
		ret = sdw_update(s_rt->slave, addr, 0xFF, p_rt->ch_mask);
	else
		ret = sdw_update(s_rt->slave, addr, 0xFF, 0x0);

	if (ret < 0)
		dev_err(&s_rt->slave->dev,
			"Slave chn_en reg write failed:%d port:%d\n",
			ret, t_params->port_num);

	return ret;
}