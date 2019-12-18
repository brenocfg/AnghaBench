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
struct rc_dev {int /*<<< orphan*/  input_dev; TYPE_1__* raw; } ;
struct imon_dec {int bits; int stick_keyboard; } ;
struct TYPE_2__ {struct imon_dec imon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  RC_PROTO_IMON ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rc_keydown (struct rc_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ir_imon_decode_scancode(struct rc_dev *dev)
{
	struct imon_dec *imon = &dev->raw->imon;

	/* Keyboard/Mouse toggle */
	if (imon->bits == 0x299115b7)
		imon->stick_keyboard = !imon->stick_keyboard;

	if ((imon->bits & 0xfc0000ff) == 0x680000b7) {
		int rel_x, rel_y;
		u8 buf;

		buf = imon->bits >> 16;
		rel_x = (buf & 0x08) | (buf & 0x10) >> 2 |
			(buf & 0x20) >> 4 | (buf & 0x40) >> 6;
		if (imon->bits & 0x02000000)
			rel_x |= ~0x0f;
		buf = imon->bits >> 8;
		rel_y = (buf & 0x08) | (buf & 0x10) >> 2 |
			(buf & 0x20) >> 4 | (buf & 0x40) >> 6;
		if (imon->bits & 0x01000000)
			rel_y |= ~0x0f;

		if (rel_x && rel_y && imon->stick_keyboard) {
			if (abs(rel_y) > abs(rel_x))
				imon->bits = rel_y > 0 ?
					0x289515b7 : /* KEY_DOWN */
					0x2aa515b7;  /* KEY_UP */
			else
				imon->bits = rel_x > 0 ?
					0x2ba515b7 : /* KEY_RIGHT */
					0x29a515b7;  /* KEY_LEFT */
		}

		if (!imon->stick_keyboard) {
			input_report_rel(dev->input_dev, REL_X, rel_x);
			input_report_rel(dev->input_dev, REL_Y, rel_y);

			input_report_key(dev->input_dev, BTN_LEFT,
					 (imon->bits & 0x00010000) != 0);
			input_report_key(dev->input_dev, BTN_RIGHT,
					 (imon->bits & 0x00040000) != 0);
		}
	}

	rc_keydown(dev, RC_PROTO_IMON, imon->bits, 0);
}