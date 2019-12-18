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
typedef  int u8 ;
struct ims_pcu {int* cmd_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMS_PCU_CMD_BOOTLOADER ; 
 int /*<<< orphan*/  IMS_PCU_RSP_BOOTLOADER ; 
 int __ims_pcu_execute_command (struct ims_pcu*,int /*<<< orphan*/ ,int*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,size_t) ; 

__attribute__((used)) static int __ims_pcu_execute_bl_command(struct ims_pcu *pcu,
				        u8 command, const void *data, size_t len,
				        u8 expected_response, int response_time)
{
	int error;

	pcu->cmd_buf[0] = command;
	if (data)
		memcpy(&pcu->cmd_buf[1], data, len);

	error = __ims_pcu_execute_command(pcu,
				IMS_PCU_CMD_BOOTLOADER, pcu->cmd_buf, len + 1,
				expected_response ? IMS_PCU_RSP_BOOTLOADER : 0,
				response_time);
	if (error) {
		dev_err(pcu->dev,
			"Failure when sending 0x%02x command to bootloader, error: %d\n",
			pcu->cmd_buf[0], error);
		return error;
	}

	if (expected_response && pcu->cmd_buf[2] != expected_response) {
		dev_err(pcu->dev,
			"Unexpected response from bootloader: 0x%02x, wanted 0x%02x\n",
			pcu->cmd_buf[2], expected_response);
		return -EINVAL;
	}

	return 0;
}