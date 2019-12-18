#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int base; int mode; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 TYPE_1__* kbdbl_ctl ; 
 scalar_t__ sony_call_snc_handle (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static ssize_t __sony_nc_kbd_backlight_mode_set(u8 value)
{
	int result;

	if (value > 2)
		return -EINVAL;

	if (sony_call_snc_handle(kbdbl_ctl->handle,
				(value << 0x10) | (kbdbl_ctl->base), &result))
		return -EIO;

	/* Try to turn the light on/off immediately */
	if (value != 1)
		sony_call_snc_handle(kbdbl_ctl->handle,
				(value << 0x0f) | (kbdbl_ctl->base + 0x100),
				&result);

	kbdbl_ctl->mode = value;

	return 0;
}