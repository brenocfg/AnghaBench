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
typedef  int u8 ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev, s32 val)
{
	u8 data;

	data = val >> 8;
	i2c_write(gspca_dev, 0x1a, &data, 1);
	data = val;
	i2c_write(gspca_dev, 0x1b, &data, 1);
}