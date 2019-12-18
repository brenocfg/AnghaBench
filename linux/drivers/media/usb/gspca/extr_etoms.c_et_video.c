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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_GPIO_OUT ; 
 int Et_WaitStatus (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int et_video(struct gspca_dev *gspca_dev,
		    int on)
{
	int ret;

	reg_w_val(gspca_dev, ET_GPIO_OUT,
		  on ? 0x10		/* startvideo - set Bit5 */
		     : 0);		/* stopvideo */
	ret = Et_WaitStatus(gspca_dev);
	if (ret != 0)
		gspca_err(gspca_dev, "timeout video on/off\n");
	return ret;
}