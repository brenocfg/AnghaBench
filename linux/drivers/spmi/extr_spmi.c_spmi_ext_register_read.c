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
typedef  int /*<<< orphan*/  u8 ;
struct spmi_device {int /*<<< orphan*/  usid; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPMI_CMD_EXT_READ ; 
 int spmi_read_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int spmi_ext_register_read(struct spmi_device *sdev, u8 addr, u8 *buf,
			   size_t len)
{
	/* 8-bit register address, up to 16 bytes */
	if (len == 0 || len > 16)
		return -EINVAL;

	return spmi_read_cmd(sdev->ctrl, SPMI_CMD_EXT_READ, sdev->usid, addr,
			     buf, len);
}