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
struct TYPE_2__ {int hue; int brightness; int sharpness; scalar_t__ backlight; scalar_t__ gamma; scalar_t__ contrast; } ;
struct sd {TYPE_1__ vold; scalar_t__ mirrorMask; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mi2020_init_post_alt (struct gspca_dev*) ; 

__attribute__((used)) static int mi2020_init_pre_alt(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->mirrorMask =  0;
	sd->vold.hue   = -1;

	/* These controls need to be reset */
	sd->vold.brightness = -1;
	sd->vold.sharpness  = -1;

	/* If not different from default, they do not need to be set */
	sd->vold.contrast  = 0;
	sd->vold.gamma     = 0;
	sd->vold.backlight = 0;

	mi2020_init_post_alt(gspca_dev);

	return 0;
}