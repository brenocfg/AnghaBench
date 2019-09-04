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
struct TYPE_3__ {scalar_t__ asic_id; } ;
struct TYPE_4__ {TYPE_1__ version; } ;
struct camera_data {int mmapped; TYPE_2__ params; } ;

/* Variables and functions */
 scalar_t__ CPIA2_ASIC_672 ; 
 int /*<<< orphan*/  CPIA2_CMD_SET_VC_MP_GPIO_DATA ; 
 int /*<<< orphan*/  CPIA2_CMD_SET_VC_MP_GPIO_DIRECTION ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRANSFER_WRITE ; 
 int /*<<< orphan*/  cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpia2_get_version_info (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_set_high_power (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_set_low_power (struct camera_data*) ; 
 int /*<<< orphan*/  reset_camera_struct (struct camera_data*) ; 

int cpia2_init_camera(struct camera_data *cam)
{
	DBG("Start\n");

	cam->mmapped = false;

	/* Get sensor and asic types before reset. */
	cpia2_set_high_power(cam);
	cpia2_get_version_info(cam);
	if (cam->params.version.asic_id != CPIA2_ASIC_672) {
		ERR("Device IO error (asicID has incorrect value of 0x%X\n",
		    cam->params.version.asic_id);
		return -ENODEV;
	}

	/* Set GPIO direction and data to a safe state. */
	cpia2_do_command(cam, CPIA2_CMD_SET_VC_MP_GPIO_DIRECTION,
			 TRANSFER_WRITE, 0);
	cpia2_do_command(cam, CPIA2_CMD_SET_VC_MP_GPIO_DATA,
			 TRANSFER_WRITE, 0);

	/* resetting struct requires version info for sensor and asic types */
	reset_camera_struct(cam);

	cpia2_set_low_power(cam);

	DBG("End\n");

	return 0;
}