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
 int /*<<< orphan*/  CX0342_RAW_BGAIN_H ; 
 int /*<<< orphan*/  CX0342_RAW_BGAIN_L ; 
 int /*<<< orphan*/  CX0342_SYS_CTRL_0 ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setbgain(struct gspca_dev *gspca_dev, s32 bgain)
{
	i2c_w(gspca_dev, CX0342_RAW_BGAIN_H, bgain >> 8);
	i2c_w(gspca_dev, CX0342_RAW_BGAIN_L, bgain);
	i2c_w(gspca_dev, CX0342_SYS_CTRL_0, 0x80);
}