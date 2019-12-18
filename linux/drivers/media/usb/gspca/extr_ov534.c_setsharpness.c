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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setsharpness(struct gspca_dev *gspca_dev, s32 val)
{
	sccb_reg_write(gspca_dev, 0x91, val);	/* Auto de-noise threshold */
	sccb_reg_write(gspca_dev, 0x8e, val);	/* De-noise threshold */
}