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
 int SAA7113_saturation ; 
 int /*<<< orphan*/  spca506_Initi2c (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca506_WriteI2c (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setcolors(struct gspca_dev *gspca_dev, s32 val)
{
	spca506_Initi2c(gspca_dev);
	spca506_WriteI2c(gspca_dev, val, SAA7113_saturation);
	spca506_WriteI2c(gspca_dev, 0x01, 0x09);
}