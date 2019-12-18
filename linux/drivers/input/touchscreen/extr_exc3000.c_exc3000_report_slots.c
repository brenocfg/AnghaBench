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
struct touchscreen_properties {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int const BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXC3000_LEN_POINT ; 
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  get_unaligned_le16 (int const*) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int const) ; 
 int /*<<< orphan*/  touchscreen_report_pos (struct input_dev*,struct touchscreen_properties*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void exc3000_report_slots(struct input_dev *input,
				 struct touchscreen_properties *prop,
				 const u8 *buf, int num)
{
	for (; num--; buf += EXC3000_LEN_POINT) {
		if (buf[0] & BIT(0)) {
			input_mt_slot(input, buf[1]);
			input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
			touchscreen_report_pos(input, prop,
					       get_unaligned_le16(buf + 2),
					       get_unaligned_le16(buf + 4),
					       true);
		}
	}
}