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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  size_t s32 ;

/* Variables and functions */
 scalar_t__ SENSOR_OV7660 ; 
#define  ov7660_50HZ 130 
#define  ov7660_60HZ 129 
#define  ov7660_NoFliker 128 
 int /*<<< orphan*/  usb_exchange (struct gspca_dev*,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static void setlightfreq(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	static const u8 (*ov7660_freq_tb[3])[4] =
		{ov7660_NoFliker, ov7660_50HZ, ov7660_60HZ};

	if (sd->sensor != SENSOR_OV7660)
		return;
	usb_exchange(gspca_dev, ov7660_freq_tb[val]);
}