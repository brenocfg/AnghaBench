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
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  S5K83A_FLIP ; 
 int S5K83A_FLIP_MASK ; 
 int /*<<< orphan*/  S5K83A_HFLIP_TUNE ; 
 int /*<<< orphan*/  S5K83A_PAGE_MAP ; 
 int /*<<< orphan*/  S5K83A_VFLIP_TUNE ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int s5k83a_set_flip_real(struct gspca_dev *gspca_dev,
				__s32 vflip, __s32 hflip)
{
	int err;
	u8 data[1];
	struct sd *sd = (struct sd *) gspca_dev;

	data[0] = 0x05;
	err = m5602_write_sensor(sd, S5K83A_PAGE_MAP, data, 1);
	if (err < 0)
		return err;

	/* six bit is vflip, seven is hflip */
	data[0] = S5K83A_FLIP_MASK;
	data[0] = (vflip) ? data[0] | 0x40 : data[0];
	data[0] = (hflip) ? data[0] | 0x80 : data[0];

	err = m5602_write_sensor(sd, S5K83A_FLIP, data, 1);
	if (err < 0)
		return err;

	data[0] = (vflip) ? 0x0b : 0x0a;
	err = m5602_write_sensor(sd, S5K83A_VFLIP_TUNE, data, 1);
	if (err < 0)
		return err;

	data[0] = (hflip) ? 0x0a : 0x0b;
	err = m5602_write_sensor(sd, S5K83A_HFLIP_TUNE, data, 1);
	return err;
}