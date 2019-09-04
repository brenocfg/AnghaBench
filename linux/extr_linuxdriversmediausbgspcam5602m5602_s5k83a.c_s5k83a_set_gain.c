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
struct sd {int dummy; } ;
struct gspca_dev {int dummy; } ;
typedef  int __s32 ;

/* Variables and functions */
 int S5K83A_GAIN ; 
 int m5602_write_sensor (struct sd*,int,int*,int) ; 

__attribute__((used)) static int s5k83a_set_gain(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	u8 data[2];
	struct sd *sd = (struct sd *) gspca_dev;

	data[0] = 0x00;
	data[1] = 0x20;
	err = m5602_write_sensor(sd, 0x14, data, 2);
	if (err < 0)
		return err;

	data[0] = 0x01;
	data[1] = 0x00;
	err = m5602_write_sensor(sd, 0x0d, data, 2);
	if (err < 0)
		return err;

	/* FIXME: This is not sane, we need to figure out the composition
		  of these registers */
	data[0] = val >> 3; /* gain, high 5 bits */
	data[1] = val >> 1; /* gain, high 7 bits */
	err = m5602_write_sensor(sd, S5K83A_GAIN, data, 2);

	return err;
}