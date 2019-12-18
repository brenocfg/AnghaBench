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
 int** cx_sensor_init ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void cx11646_init1(struct gspca_dev *gspca_dev)
{
	int i = 0;

	reg_w_val(gspca_dev, 0x0010, 0x00);
	reg_w_val(gspca_dev, 0x0053, 0x00);
	reg_w_val(gspca_dev, 0x0052, 0x00);
	reg_w_val(gspca_dev, 0x009b, 0x2f);
	reg_w_val(gspca_dev, 0x009c, 0x10);
	reg_r(gspca_dev, 0x0098, 1);
	reg_w_val(gspca_dev, 0x0098, 0x40);
	reg_r(gspca_dev, 0x0099, 1);
	reg_w_val(gspca_dev, 0x0099, 0x07);
	reg_w_val(gspca_dev, 0x0039, 0x40);
	reg_w_val(gspca_dev, 0x003c, 0xff);
	reg_w_val(gspca_dev, 0x003f, 0x1f);
	reg_w_val(gspca_dev, 0x003d, 0x40);
/*	reg_w_val(gspca_dev, 0x003d, 0x60); */
	reg_r(gspca_dev, 0x0099, 1);			/* ->0x07 */

	while (cx_sensor_init[i][0]) {
		reg_w_val(gspca_dev, 0x00e5, cx_sensor_init[i][0]);
		reg_r(gspca_dev, 0x00e8, 1);		/* -> 0x00 */
		if (i == 1) {
			reg_w_val(gspca_dev, 0x00ed, 0x01);
			reg_r(gspca_dev, 0x00ed, 1);	/* -> 0x01 */
		}
		i++;
	}
	reg_w_val(gspca_dev, 0x00c3, 0x00);
}