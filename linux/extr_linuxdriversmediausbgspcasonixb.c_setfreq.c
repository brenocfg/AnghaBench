#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sd {size_t sensor; TYPE_1__* plfreq; } ;
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;
struct TYPE_4__ {int sensor_addr; } ;
struct TYPE_3__ {int val; } ;

/* Variables and functions */
 size_t SENSOR_OV6650 ; 
 size_t SENSOR_OV7630 ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int*) ; 
 TYPE_2__* sensor_data ; 

__attribute__((used)) static void setfreq(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_OV6650 || sd->sensor == SENSOR_OV7630) {
		/* Framerate adjust register for artificial light 50 hz flicker
		   compensation, for the ov6650 this is identical to ov6630
		   0x2b register, see ov6630 datasheet.
		   0x4f / 0x8a -> (30 fps -> 25 fps), 0x00 -> no adjustment */
		__u8 i2c[] = {0xa0, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x10};
		switch (sd->plfreq->val) {
		default:
/*		case 0:			 * no filter*/
/*		case 2:			 * 60 hz */
			i2c[3] = 0;
			break;
		case 1:			/* 50 hz */
			i2c[3] = (sd->sensor == SENSOR_OV6650)
					? 0x4f : 0x8a;
			break;
		}
		i2c[1] = sensor_data[sd->sensor].sensor_addr;
		i2c_w(gspca_dev, i2c);
	}
}