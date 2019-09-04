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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_validx (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbl_commmon ; 
 int /*<<< orphan*/  tbl_init_at_startup ; 

__attribute__((used)) static int ov9655_init_at_startup(struct gspca_dev *gspca_dev)
{
	fetch_validx(gspca_dev, tbl_init_at_startup,
			ARRAY_SIZE(tbl_init_at_startup));
	fetch_validx(gspca_dev, tbl_commmon, ARRAY_SIZE(tbl_commmon));
/*	ctrl_out(gspca_dev, 0x40, 11, 0x0000, 0x0000, 0, NULL);*/

	return 0;
}