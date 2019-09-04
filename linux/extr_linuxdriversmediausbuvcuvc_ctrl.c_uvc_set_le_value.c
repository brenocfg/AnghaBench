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
struct uvc_control_mapping {int size; int offset; scalar_t__ v4l2_type; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ V4L2_CTRL_TYPE_BUTTON ; 

__attribute__((used)) static void uvc_set_le_value(struct uvc_control_mapping *mapping,
	s32 value, u8 *data)
{
	int bits = mapping->size;
	int offset = mapping->offset;
	u8 mask;

	/* According to the v4l2 spec, writing any value to a button control
	 * should result in the action belonging to the button control being
	 * triggered. UVC devices however want to see a 1 written -> override
	 * value.
	 */
	if (mapping->v4l2_type == V4L2_CTRL_TYPE_BUTTON)
		value = -1;

	data += offset / 8;
	offset &= 7;

	for (; bits > 0; data++) {
		mask = ((1LL << bits) - 1) << offset;
		*data = (*data & ~mask) | ((value << offset) & mask);
		value >>= offset ? offset : 8;
		bits -= 8 - offset;
		offset = 0;
	}
}