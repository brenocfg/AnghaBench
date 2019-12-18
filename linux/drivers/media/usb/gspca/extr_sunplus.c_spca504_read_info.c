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
typedef  int /*<<< orphan*/  u8 ;
struct gspca_dev {int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 scalar_t__ D_STREAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gspca_debug ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void spca504_read_info(struct gspca_dev *gspca_dev)
{
	int i;
	u8 info[6];

	if (gspca_debug < D_STREAM)
		return;

	for (i = 0; i < 6; i++) {
		reg_r(gspca_dev, 0, i, 1);
		info[i] = gspca_dev->usb_buf[0];
	}
	gspca_dbg(gspca_dev, D_STREAM,
		  "Read info: %d %d %d %d %d %d. Should be 1,0,2,2,0,0\n",
		  info[0], info[1], info[2],
		  info[3], info[4], info[5]);
}