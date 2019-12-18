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
 int /*<<< orphan*/  CX0342_RAW_RGAIN_H ; 
 int /*<<< orphan*/  CX0342_RAW_RGAIN_L ; 
 int /*<<< orphan*/  CX0342_SYS_CTRL_0 ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setrgain(struct gspca_dev *gspca_dev, s32 rgain)
{
	i2c_w(gspca_dev, CX0342_RAW_RGAIN_H, rgain >> 8);
	i2c_w(gspca_dev, CX0342_RAW_RGAIN_L, rgain);
	i2c_w(gspca_dev, CX0342_SYS_CTRL_0, 0x80);
}