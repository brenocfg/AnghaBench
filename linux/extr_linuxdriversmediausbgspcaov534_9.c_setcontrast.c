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
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setcontrast(struct gspca_dev *gspca_dev, s32 val)
{
	sccb_write(gspca_dev, 0x56,	/* cnst1 - contrast 1 ctrl coeff */
			val << 4);
}