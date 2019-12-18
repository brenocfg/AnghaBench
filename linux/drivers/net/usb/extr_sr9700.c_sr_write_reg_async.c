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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_REQ_WR_REG ; 
 int /*<<< orphan*/  SR_WR_REGS ; 
 int /*<<< orphan*/  usbnet_write_cmd_async (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sr_write_reg_async(struct usbnet *dev, u8 reg, u8 value)
{
	usbnet_write_cmd_async(dev, SR_WR_REGS, SR_REQ_WR_REG,
			       value, reg, NULL, 0);
}