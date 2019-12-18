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
typedef  int u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SR_REQ_WR_REG ; 
 int /*<<< orphan*/  SR_WR_REGS ; 
 int usbnet_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int sr_write(struct usbnet *dev, u8 reg, u16 length, void *data)
{
	int err;

	err = usbnet_write_cmd(dev, SR_WR_REGS, SR_REQ_WR_REG, 0, reg, data,
			       length);
	if ((err >= 0) && (err < length))
		err = -EINVAL;
	return err;
}