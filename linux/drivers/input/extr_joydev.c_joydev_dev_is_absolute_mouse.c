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
struct TYPE_2__ {scalar_t__ bustype; } ;
struct input_dev {TYPE_1__ id; int /*<<< orphan*/  keybit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 scalar_t__ ABS_CNT ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ BUS_AMIGA ; 
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  EV_ABS ; 
 scalar_t__ EV_CNT ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  EV_SYN ; 
 scalar_t__ KEY_CNT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jd_scratch ; 

__attribute__((used)) static bool joydev_dev_is_absolute_mouse(struct input_dev *dev)
{
	DECLARE_BITMAP(jd_scratch, KEY_CNT);
	bool ev_match = false;

	BUILD_BUG_ON(ABS_CNT > KEY_CNT || EV_CNT > KEY_CNT);

	/*
	 * Virtualization (VMware, etc) and remote management (HP
	 * ILO2) solutions use absolute coordinates for their virtual
	 * pointing devices so that there is one-to-one relationship
	 * between pointer position on the host screen and virtual
	 * guest screen, and so their mice use ABS_X, ABS_Y and 3
	 * primary button events. This clashes with what joydev
	 * considers to be joysticks (a device with at minimum ABS_X
	 * axis).
	 *
	 * Here we are trying to separate absolute mice from
	 * joysticks. A device is, for joystick detection purposes,
	 * considered to be an absolute mouse if the following is
	 * true:
	 *
	 * 1) Event types are exactly
	 *      EV_ABS, EV_KEY and EV_SYN
	 *    or
	 *      EV_ABS, EV_KEY, EV_SYN and EV_MSC
	 *    or
	 *      EV_ABS, EV_KEY, EV_SYN, EV_MSC and EV_REL.
	 * 2) Absolute events are exactly ABS_X and ABS_Y.
	 * 3) Keys are exactly BTN_LEFT, BTN_RIGHT and BTN_MIDDLE.
	 * 4) Device is not on "Amiga" bus.
	 */

	bitmap_zero(jd_scratch, EV_CNT);
	/* VMware VMMouse, HP ILO2 */
	__set_bit(EV_ABS, jd_scratch);
	__set_bit(EV_KEY, jd_scratch);
	__set_bit(EV_SYN, jd_scratch);
	if (bitmap_equal(jd_scratch, dev->evbit, EV_CNT))
		ev_match = true;

	/* HP ILO2, AMI BMC firmware */
	__set_bit(EV_MSC, jd_scratch);
	if (bitmap_equal(jd_scratch, dev->evbit, EV_CNT))
		ev_match = true;

	/* VMware Virtual USB Mouse, QEMU USB Tablet, ATEN BMC firmware */
	__set_bit(EV_REL, jd_scratch);
	if (bitmap_equal(jd_scratch, dev->evbit, EV_CNT))
		ev_match = true;

	if (!ev_match)
		return false;

	bitmap_zero(jd_scratch, ABS_CNT);
	__set_bit(ABS_X, jd_scratch);
	__set_bit(ABS_Y, jd_scratch);
	if (!bitmap_equal(dev->absbit, jd_scratch, ABS_CNT))
		return false;

	bitmap_zero(jd_scratch, KEY_CNT);
	__set_bit(BTN_LEFT, jd_scratch);
	__set_bit(BTN_RIGHT, jd_scratch);
	__set_bit(BTN_MIDDLE, jd_scratch);

	if (!bitmap_equal(dev->keybit, jd_scratch, KEY_CNT))
		return false;

	/*
	 * Amiga joystick (amijoy) historically uses left/middle/right
	 * button events.
	 */
	if (dev->id.bustype == BUS_AMIGA)
		return false;

	return true;
}