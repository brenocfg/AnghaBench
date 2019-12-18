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
struct kbd_info {int modes; int type; int triggers; int levels; int seconds; int minutes; int hours; int days; } ;
struct calling_interface_buffer {int* output; } ;
struct TYPE_2__ {scalar_t__ kbd_led_levels_off_1; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CLASS_KBD_BACKLIGHT ; 
 int /*<<< orphan*/  SELECT_KBD_BACKLIGHT ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* quirks ; 

__attribute__((used)) static int kbd_get_info(struct kbd_info *info)
{
	struct calling_interface_buffer buffer;
	u8 units;
	int ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer,
				CLASS_KBD_BACKLIGHT, SELECT_KBD_BACKLIGHT);
	if (ret)
		return ret;

	info->modes = buffer.output[1] & 0xFFFF;
	info->type = (buffer.output[1] >> 24) & 0xFF;
	info->triggers = buffer.output[2] & 0xFF;
	units = (buffer.output[2] >> 8) & 0xFF;
	info->levels = (buffer.output[2] >> 16) & 0xFF;

	if (quirks && quirks->kbd_led_levels_off_1 && info->levels)
		info->levels--;

	if (units & BIT(0))
		info->seconds = (buffer.output[3] >> 0) & 0xFF;
	if (units & BIT(1))
		info->minutes = (buffer.output[3] >> 8) & 0xFF;
	if (units & BIT(2))
		info->hours = (buffer.output[3] >> 16) & 0xFF;
	if (units & BIT(3))
		info->days = (buffer.output[3] >> 24) & 0xFF;

	return ret;
}