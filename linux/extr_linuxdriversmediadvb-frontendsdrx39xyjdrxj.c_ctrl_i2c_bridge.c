#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct drxj_hi_cmd {int /*<<< orphan*/  param2; int /*<<< orphan*/  param1; int /*<<< orphan*/  cmd; } ;
struct drx_demod_instance {int /*<<< orphan*/  my_i2c_dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SIO_HI_RA_RAM_CMD_BRDCTRL ; 
 int /*<<< orphan*/  SIO_HI_RA_RAM_PAR_1_PAR1_SEC_KEY ; 
 int /*<<< orphan*/  SIO_HI_RA_RAM_PAR_2_BRD_CFG_CLOSED ; 
 int /*<<< orphan*/  SIO_HI_RA_RAM_PAR_2_BRD_CFG_OPEN ; 
 int hi_command (int /*<<< orphan*/ ,struct drxj_hi_cmd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctrl_i2c_bridge(struct drx_demod_instance *demod, bool *bridge_closed)
{
	struct drxj_hi_cmd hi_cmd;
	u16 result = 0;

	/* check arguments */
	if (bridge_closed == NULL)
		return -EINVAL;

	hi_cmd.cmd = SIO_HI_RA_RAM_CMD_BRDCTRL;
	hi_cmd.param1 = SIO_HI_RA_RAM_PAR_1_PAR1_SEC_KEY;
	if (*bridge_closed)
		hi_cmd.param2 = SIO_HI_RA_RAM_PAR_2_BRD_CFG_CLOSED;
	else
		hi_cmd.param2 = SIO_HI_RA_RAM_PAR_2_BRD_CFG_OPEN;

	return hi_command(demod->my_i2c_dev_addr, &hi_cmd, &result);
}