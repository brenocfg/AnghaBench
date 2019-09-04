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
struct camera_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_GET_ASIC_TYPE ; 
 int /*<<< orphan*/  CPIA2_CMD_GET_PNP_ID ; 
 int /*<<< orphan*/  CPIA2_CMD_GET_SENSOR ; 
 int /*<<< orphan*/  CPIA2_CMD_GET_VERSION ; 
 int /*<<< orphan*/  CPIA2_CMD_GET_VP_DEVICE ; 
 int /*<<< orphan*/  TRANSFER_READ ; 
 int /*<<< orphan*/  cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpia2_get_version_info(struct camera_data *cam)
{
	cpia2_do_command(cam, CPIA2_CMD_GET_VERSION, TRANSFER_READ, 0);
	cpia2_do_command(cam, CPIA2_CMD_GET_PNP_ID, TRANSFER_READ, 0);
	cpia2_do_command(cam, CPIA2_CMD_GET_ASIC_TYPE, TRANSFER_READ, 0);
	cpia2_do_command(cam, CPIA2_CMD_GET_SENSOR, TRANSFER_READ, 0);
	cpia2_do_command(cam, CPIA2_CMD_GET_VP_DEVICE, TRANSFER_READ, 0);
}