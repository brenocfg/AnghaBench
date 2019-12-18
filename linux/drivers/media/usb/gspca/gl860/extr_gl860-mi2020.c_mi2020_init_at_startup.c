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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common (struct gspca_dev*) ; 
 int /*<<< orphan*/  ctrl_in (struct gspca_dev*,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_validx (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tbl_init_at_startup ; 

__attribute__((used)) static int mi2020_init_at_startup(struct gspca_dev *gspca_dev)
{
	u8 c;

	ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0004, 1, &c);
	ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0004, 1, &c);

	fetch_validx(gspca_dev, tbl_init_at_startup,
			ARRAY_SIZE(tbl_init_at_startup));

	ctrl_out(gspca_dev, 0x40,  1, 0x7a00, 0x8030,  0, NULL);
	ctrl_in(gspca_dev, 0xc0,  2, 0x7a00, 0x8030,  1, &c);

	common(gspca_dev);

	msleep(61);
/*	ctrl_out(gspca_dev, 0x40, 11, 0x0000, 0x0000,  0, NULL); */
/*	msleep(36); */
	ctrl_out(gspca_dev, 0x40,  1, 0x0001, 0x0000,  0, NULL);

	return 0;
}