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
struct validx {int idx; int val; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

int keep_on_fetching_validx(struct gspca_dev *gspca_dev, struct validx *tbl,
				int len, int n)
{
	while (++n < len) {
		if (tbl[n].idx != 0xffff)
			ctrl_out(gspca_dev, 0x40, 1, tbl[n].val, tbl[n].idx,
					0, NULL);
		else if (tbl[n].val == 0xffff)
			break;
		else
			msleep(tbl[n].val);
	}
	return n;
}