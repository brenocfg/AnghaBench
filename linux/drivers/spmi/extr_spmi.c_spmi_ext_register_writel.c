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
typedef  int /*<<< orphan*/  u16 ;
struct spmi_device {int /*<<< orphan*/  usid; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPMI_CMD_EXT_WRITEL ; 
 int spmi_write_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int spmi_ext_register_writel(struct spmi_device *sdev, u16 addr, const u8 *buf,
			     size_t len)
{
	/* 4-bit Slave Identifier, 16-bit register address, up to 8 bytes */
	if (len == 0 || len > 8)
		return -EINVAL;

	return spmi_write_cmd(sdev->ctrl, SPMI_CMD_EXT_WRITEL, sdev->usid,
			      addr, buf, len);
}