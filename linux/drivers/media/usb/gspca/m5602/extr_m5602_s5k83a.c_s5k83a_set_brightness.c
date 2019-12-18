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
struct sd {int dummy; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  S5K83A_BRIGHTNESS ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int s5k83a_set_brightness(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	u8 data[1];
	struct sd *sd = (struct sd *) gspca_dev;

	data[0] = val;
	err = m5602_write_sensor(sd, S5K83A_BRIGHTNESS, data, 1);
	return err;
}