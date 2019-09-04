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
struct sd {int flip_debounce; int flip_status; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sethflip (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvflip (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stk1135_dq_callback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->flip_debounce > 100) {
		sd->flip_status = !sd->flip_status;
		sethflip(gspca_dev, v4l2_ctrl_g_ctrl(sd->hflip));
		setvflip(gspca_dev, v4l2_ctrl_g_ctrl(sd->vflip));
	}
}