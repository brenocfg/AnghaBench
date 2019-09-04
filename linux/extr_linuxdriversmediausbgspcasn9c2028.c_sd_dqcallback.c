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
struct sd {int /*<<< orphan*/  avg_lum; int /*<<< orphan*/ * autogain; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_autogain (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sd_dqcallback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->autogain == NULL || !v4l2_ctrl_g_ctrl(sd->autogain))
		return;

	do_autogain(gspca_dev, sd->avg_lum);
}