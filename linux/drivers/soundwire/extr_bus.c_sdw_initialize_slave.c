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
typedef  int u8 ;
struct sdw_slave_prop {TYPE_1__* dp0_prop; } ;
struct sdw_slave {TYPE_2__* bus; struct sdw_slave_prop prop; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int imp_def_interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDW_DP0_INTMASK ; 
 int SDW_DP0_INT_BRA_FAILURE ; 
 int SDW_DP0_INT_PORT_READY ; 
 int SDW_SCP_INT1_BUS_CLASH ; 
 int SDW_SCP_INT1_IMPL_DEF ; 
 int SDW_SCP_INT1_PARITY ; 
 int /*<<< orphan*/  SDW_SCP_INTMASK1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sdw_update (struct sdw_slave*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sdw_initialize_slave(struct sdw_slave *slave)
{
	struct sdw_slave_prop *prop = &slave->prop;
	int ret;
	u8 val;

	/*
	 * Set bus clash, parity and SCP implementation
	 * defined interrupt mask
	 * TODO: Read implementation defined interrupt mask
	 * from Slave property
	 */
	val = SDW_SCP_INT1_IMPL_DEF | SDW_SCP_INT1_BUS_CLASH |
					SDW_SCP_INT1_PARITY;

	/* Enable SCP interrupts */
	ret = sdw_update(slave, SDW_SCP_INTMASK1, val, val);
	if (ret < 0) {
		dev_err(slave->bus->dev,
			"SDW_SCP_INTMASK1 write failed:%d\n", ret);
		return ret;
	}

	/* No need to continue if DP0 is not present */
	if (!slave->prop.dp0_prop)
		return 0;

	/* Enable DP0 interrupts */
	val = prop->dp0_prop->imp_def_interrupts;
	val |= SDW_DP0_INT_PORT_READY | SDW_DP0_INT_BRA_FAILURE;

	ret = sdw_update(slave, SDW_DP0_INTMASK, val, val);
	if (ret < 0) {
		dev_err(slave->bus->dev,
			"SDW_DP0_INTMASK read failed:%d\n", ret);
		return val;
	}

	return 0;
}