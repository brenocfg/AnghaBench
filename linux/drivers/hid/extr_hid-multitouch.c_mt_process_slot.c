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
struct mt_usages {int* inrange_state; int* tip_state; int* confidence_state; scalar_t__* w; scalar_t__* h; int* a; int* x; int* y; int* cx; int* cy; int* p; } ;
struct mt_device {int maxcontacts; int /*<<< orphan*/  mt_io_flags; } ;
struct mt_application {int quirks; scalar_t__ num_received; scalar_t__ num_expected; scalar_t__ application; int /*<<< orphan*/ * pending_palm_slots; } ;
struct input_mt_slot {int dummy; } ;
struct input_mt {struct input_mt_slot* slots; } ;
struct input_dev {struct input_mt* mt; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_DISTANCE ; 
 int /*<<< orphan*/  ABS_MT_ORIENTATION ; 
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TOOL_X ; 
 int /*<<< orphan*/  ABS_MT_TOOL_Y ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MAJOR ; 
 int /*<<< orphan*/  ABS_MT_TOUCH_MINOR ; 
 int* DEFAULT_ZERO ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  EV_ABS ; 
 scalar_t__ HID_GD_SYSTEM_MULTIAXIS ; 
 int MT_IO_FLAGS_ACTIVE_SLOTS ; 
 int MT_QUIRK_ALWAYS_VALID ; 
 int MT_QUIRK_CONFIDENCE ; 
 int MT_QUIRK_CONTACT_CNT_ACCURATE ; 
 int MT_QUIRK_HOVERING ; 
 int MT_QUIRK_IGNORE_DUPLICATES ; 
 int MT_QUIRK_NOT_SEEN_MEANS_UP ; 
 int MT_QUIRK_TOUCH_SIZE_SCALING ; 
 int MT_QUIRK_VALID_IS_CONFIDENCE ; 
 int MT_QUIRK_VALID_IS_INRANGE ; 
 int MT_TOOL_DIAL ; 
 int MT_TOOL_FINGER ; 
 int MT_TOOL_PALM ; 
 int input_abs_get_max (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ input_mt_is_active (struct input_mt_slot*) ; 
 scalar_t__ input_mt_is_used (struct input_mt*,struct input_mt_slot*) ; 
 int /*<<< orphan*/  input_mt_report_slot_state (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_mt_slot (struct input_dev*,int) ; 
 int max (scalar_t__,scalar_t__) ; 
 int min (scalar_t__,scalar_t__) ; 
 int mt_compute_slot (struct mt_device*,struct mt_application*,struct mt_usages*,struct input_dev*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mt_process_slot(struct mt_device *td, struct input_dev *input,
			    struct mt_application *app,
			    struct mt_usages *slot)
{
	struct input_mt *mt = input->mt;
	__s32 quirks = app->quirks;
	bool valid = true;
	bool confidence_state = true;
	bool inrange_state = false;
	int active;
	int slotnum;
	int tool = MT_TOOL_FINGER;

	if (!slot)
		return -EINVAL;

	if ((quirks & MT_QUIRK_CONTACT_CNT_ACCURATE) &&
	    app->num_received >= app->num_expected)
		return -EAGAIN;

	if (!(quirks & MT_QUIRK_ALWAYS_VALID)) {
		if (quirks & MT_QUIRK_VALID_IS_INRANGE)
			valid = *slot->inrange_state;
		if (quirks & MT_QUIRK_NOT_SEEN_MEANS_UP)
			valid = *slot->tip_state;
		if (quirks & MT_QUIRK_VALID_IS_CONFIDENCE)
			valid = *slot->confidence_state;

		if (!valid)
			return 0;
	}

	slotnum = mt_compute_slot(td, app, slot, input);
	if (slotnum < 0 || slotnum >= td->maxcontacts)
		return 0;

	if ((quirks & MT_QUIRK_IGNORE_DUPLICATES) && mt) {
		struct input_mt_slot *i_slot = &mt->slots[slotnum];

		if (input_mt_is_active(i_slot) &&
		    input_mt_is_used(mt, i_slot))
			return -EAGAIN;
	}

	if (quirks & MT_QUIRK_CONFIDENCE)
		confidence_state = *slot->confidence_state;

	if (quirks & MT_QUIRK_HOVERING)
		inrange_state = *slot->inrange_state;

	active = *slot->tip_state || inrange_state;

	if (app->application == HID_GD_SYSTEM_MULTIAXIS)
		tool = MT_TOOL_DIAL;
	else if (unlikely(!confidence_state)) {
		tool = MT_TOOL_PALM;
		if (!active &&
		    input_mt_is_active(&mt->slots[slotnum])) {
			/*
			 * The non-confidence was reported for
			 * previously valid contact that is also no
			 * longer valid. We can't simply report
			 * lift-off as userspace will not be aware
			 * of non-confidence, so we need to split
			 * it into 2 events: active MT_TOOL_PALM
			 * and a separate liftoff.
			 */
			active = true;
			set_bit(slotnum, app->pending_palm_slots);
		}
	}

	input_mt_slot(input, slotnum);
	input_mt_report_slot_state(input, tool, active);
	if (active) {
		/* this finger is in proximity of the sensor */
		int wide = (*slot->w > *slot->h);
		int major = max(*slot->w, *slot->h);
		int minor = min(*slot->w, *slot->h);
		int orientation = wide;
		int max_azimuth;
		int azimuth;

		if (slot->a != DEFAULT_ZERO) {
			/*
			 * Azimuth is counter-clockwise and ranges from [0, MAX)
			 * (a full revolution). Convert it to clockwise ranging
			 * [-MAX/2, MAX/2].
			 *
			 * Note that ABS_MT_ORIENTATION require us to report
			 * the limit of [-MAX/4, MAX/4], but the value can go
			 * out of range to [-MAX/2, MAX/2] to report an upside
			 * down ellipsis.
			 */
			azimuth = *slot->a;
			max_azimuth = input_abs_get_max(input,
							ABS_MT_ORIENTATION);
			if (azimuth > max_azimuth * 2)
				azimuth -= max_azimuth * 4;
			orientation = -azimuth;
		}

		if (quirks & MT_QUIRK_TOUCH_SIZE_SCALING) {
			/*
			 * divided by two to match visual scale of touch
			 * for devices with this quirk
			 */
			major = major >> 1;
			minor = minor >> 1;
		}

		input_event(input, EV_ABS, ABS_MT_POSITION_X, *slot->x);
		input_event(input, EV_ABS, ABS_MT_POSITION_Y, *slot->y);
		input_event(input, EV_ABS, ABS_MT_TOOL_X, *slot->cx);
		input_event(input, EV_ABS, ABS_MT_TOOL_Y, *slot->cy);
		input_event(input, EV_ABS, ABS_MT_DISTANCE, !*slot->tip_state);
		input_event(input, EV_ABS, ABS_MT_ORIENTATION, orientation);
		input_event(input, EV_ABS, ABS_MT_PRESSURE, *slot->p);
		input_event(input, EV_ABS, ABS_MT_TOUCH_MAJOR, major);
		input_event(input, EV_ABS, ABS_MT_TOUCH_MINOR, minor);

		set_bit(MT_IO_FLAGS_ACTIVE_SLOTS, &td->mt_io_flags);
	}

	return 0;
}