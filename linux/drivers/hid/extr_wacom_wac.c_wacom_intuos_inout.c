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
struct wacom_features {scalar_t__ type; int /*<<< orphan*/  distance_max; } ;
struct wacom_wac {unsigned char* data; unsigned char* serial; unsigned char* id; int reporting_data; TYPE_1__* shared; struct wacom_features features; int /*<<< orphan*/ * tool; struct input_dev* pen_input; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int stylus_in_proximity; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ INTUOS ; 
 scalar_t__ INTUOSHT2 ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_exit_report (struct wacom_wac*) ; 
 int /*<<< orphan*/  wacom_intuos_get_tool_type (unsigned char) ; 

__attribute__((used)) static int wacom_intuos_inout(struct wacom_wac *wacom)
{
	struct wacom_features *features = &wacom->features;
	unsigned char *data = wacom->data;
	struct input_dev *input = wacom->pen_input;
	int idx = (features->type == INTUOS) ? (data[1] & 0x01) : 0;

	if (!(((data[1] & 0xfc) == 0xc0) ||  /* in prox */
	    ((data[1] & 0xfe) == 0x20) ||    /* in range */
	    ((data[1] & 0xfe) == 0x80)))     /* out prox */
		return 0;

	/* Enter report */
	if ((data[1] & 0xfc) == 0xc0) {
		/* serial number of the tool */
		wacom->serial[idx] = ((data[3] & 0x0f) << 28) +
			(data[4] << 20) + (data[5] << 12) +
			(data[6] << 4) + (data[7] >> 4);

		wacom->id[idx] = (data[2] << 4) | (data[3] >> 4) |
		     ((data[7] & 0x0f) << 16) | ((data[8] & 0xf0) << 8);

		wacom->tool[idx] = wacom_intuos_get_tool_type(wacom->id[idx]);

		wacom->shared->stylus_in_proximity = true;
		return 1;
	}

	/* in Range */
	if ((data[1] & 0xfe) == 0x20) {
		if (features->type != INTUOSHT2)
			wacom->shared->stylus_in_proximity = true;

		/* in Range while exiting */
		if (wacom->reporting_data) {
			input_report_key(input, BTN_TOUCH, 0);
			input_report_abs(input, ABS_PRESSURE, 0);
			input_report_abs(input, ABS_DISTANCE, wacom->features.distance_max);
			return 2;
		}
		return 1;
	}

	/* Exit report */
	if ((data[1] & 0xfe) == 0x80) {
		wacom->shared->stylus_in_proximity = false;
		wacom->reporting_data = false;

		/* don't report exit if we don't know the ID */
		if (!wacom->id[idx])
			return 1;

		wacom_exit_report(wacom);
		return 2;
	}

	return 0;
}