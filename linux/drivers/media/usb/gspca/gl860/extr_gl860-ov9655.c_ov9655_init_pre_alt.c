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
struct TYPE_2__ {int brightness; int hue; } ;
struct sd {TYPE_1__ vold; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_validx (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov9655_init_post_alt (struct gspca_dev*) ; 
 int /*<<< orphan*/  tbl_commmon ; 

__attribute__((used)) static int ov9655_init_pre_alt(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->vold.brightness = -1;
	sd->vold.hue = -1;

	fetch_validx(gspca_dev, tbl_commmon, ARRAY_SIZE(tbl_commmon));

	ov9655_init_post_alt(gspca_dev);

	return 0;
}