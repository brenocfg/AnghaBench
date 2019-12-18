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
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_MCUFWDL ; 
 int usb_read8 (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void _rtl88e_enable_fw_download(struct adapter *adapt, bool enable)
{
	u8 tmp;

	if (enable) {
		tmp = usb_read8(adapt, REG_MCUFWDL);
		usb_write8(adapt, REG_MCUFWDL, tmp | 0x01);

		tmp = usb_read8(adapt, REG_MCUFWDL + 2);
		usb_write8(adapt, REG_MCUFWDL + 2, tmp & 0xf7);
	} else {
		tmp = usb_read8(adapt, REG_MCUFWDL);
		usb_write8(adapt, REG_MCUFWDL, tmp & 0xfe);

		usb_write8(adapt, REG_MCUFWDL + 1, 0x00);
	}
}