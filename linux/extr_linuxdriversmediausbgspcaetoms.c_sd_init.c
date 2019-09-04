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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_RESET_ALL ; 
 int /*<<< orphan*/  Et_init1 (struct gspca_dev*) ; 
 int /*<<< orphan*/  Et_init2 (struct gspca_dev*) ; 
 scalar_t__ SENSOR_PAS106 ; 
 int /*<<< orphan*/  et_video (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_PAS106)
		Et_init1(gspca_dev);
	else
		Et_init2(gspca_dev);
	reg_w_val(gspca_dev, ET_RESET_ALL, 0x08);
	et_video(gspca_dev, 0);		/* video off */
	return 0;
}