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
struct v4l2_subdev {int dummy; } ;
struct m5mols_info {int isp_ready; int /*<<< orphan*/  irq_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_CAM_START ; 
 int M5MOLS_I2C_RDY_WAIT_FL ; 
 int /*<<< orphan*/  PARM_INTERFACE ; 
 int /*<<< orphan*/  REG_INTERFACE_MIPI ; 
 int REG_INT_AF ; 
 int REG_INT_CAPTURE ; 
 int /*<<< orphan*/  REG_INT_MODE ; 
 int /*<<< orphan*/  REG_IN_FLASH_MODE ; 
 int /*<<< orphan*/  REG_START_ARM_BOOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int m5mols_busy_wait (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  m5mols_debug ; 
 int m5mols_enable_interrupt (struct v4l2_subdev*,int) ; 
 int m5mols_get_version (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  m5mols_sensor_power ; 
 int m5mols_update_fw (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int m5mols_wait_interrupt (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int m5mols_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct m5mols_info* to_m5mols (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int m5mols_fw_start(struct v4l2_subdev *sd)
{
	struct m5mols_info *info = to_m5mols(sd);
	int ret;

	atomic_set(&info->irq_done, 0);
	/* Wait until I2C slave is initialized in Flash Writer mode */
	ret = m5mols_busy_wait(sd, FLASH_CAM_START, REG_IN_FLASH_MODE,
			       M5MOLS_I2C_RDY_WAIT_FL | 0xff, -1);
	if (!ret)
		ret = m5mols_write(sd, FLASH_CAM_START, REG_START_ARM_BOOT);
	if (!ret)
		ret = m5mols_wait_interrupt(sd, REG_INT_MODE, 2000);
	if (ret < 0)
		return ret;

	info->isp_ready = 1;

	ret = m5mols_get_version(sd);
	if (!ret)
		ret = m5mols_update_fw(sd, m5mols_sensor_power);
	if (ret)
		return ret;

	v4l2_dbg(1, m5mols_debug, sd, "Success ARM Booting\n");

	ret = m5mols_write(sd, PARM_INTERFACE, REG_INTERFACE_MIPI);
	if (!ret)
		ret = m5mols_enable_interrupt(sd,
				REG_INT_AF | REG_INT_CAPTURE);

	return ret;
}