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
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int reg_r_wait (struct gspca_dev*,int,int,int) ; 
 int reg_w (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static int spca500_full_reset(struct gspca_dev *gspca_dev)
{
	int err;

	/* send the reset command */
	err = reg_w(gspca_dev, 0xe0, 0x0001, 0x0000);
	if (err < 0)
		return err;

	/* wait for the reset to complete */
	err = reg_r_wait(gspca_dev, 0x06, 0x0000, 0x0000);
	if (err < 0)
		return err;
	err = reg_w(gspca_dev, 0xe0, 0x0000, 0x0000);
	if (err < 0)
		return err;
	err = reg_r_wait(gspca_dev, 0x06, 0, 0);
	if (err < 0) {
		gspca_err(gspca_dev, "reg_r_wait() failed\n");
		return err;
	}
	/* all ok */
	return 0;
}