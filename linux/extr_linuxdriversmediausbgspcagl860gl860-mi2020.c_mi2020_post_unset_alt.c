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
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void mi2020_post_unset_alt(struct gspca_dev *gspca_dev)
{
	ctrl_out(gspca_dev, 0x40, 5, 0x0000, 0x0000, 0, NULL);
	msleep(40);
	ctrl_out(gspca_dev, 0x40, 1, 0x0001, 0x0000, 0, NULL);
}