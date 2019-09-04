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
struct sd {scalar_t__ autogain_ignore_frames; TYPE_1__* brightness; int /*<<< orphan*/  avg_lum; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAC7302_EXPOSURE_KNEE ; 
 int /*<<< orphan*/  PAC7302_GAIN_KNEE ; 
 scalar_t__ PAC_AUTOGAIN_IGNORE_FRAMES ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ gspca_expo_autogain (struct gspca_dev*,int,int,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_autogain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int avg_lum = atomic_read(&sd->avg_lum);
	int desired_lum;
	const int deadzone = 30;

	if (sd->autogain_ignore_frames < 0)
		return;

	if (sd->autogain_ignore_frames > 0) {
		sd->autogain_ignore_frames--;
	} else {
		desired_lum = 270 + sd->brightness->val;

		if (gspca_expo_autogain(gspca_dev, avg_lum, desired_lum,
					deadzone, PAC7302_GAIN_KNEE,
					PAC7302_EXPOSURE_KNEE))
			sd->autogain_ignore_frames =
						PAC_AUTOGAIN_IGNORE_FRAMES;
	}
}