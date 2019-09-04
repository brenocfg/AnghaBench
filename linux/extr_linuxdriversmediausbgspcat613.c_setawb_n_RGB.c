#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sd {size_t sensor; TYPE_4__* awb; TYPE_3__* blue_balance; TYPE_2__* red_balance; TYPE_1__* gain; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;
struct TYPE_10__ {int reg80; } ;
struct TYPE_9__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {int val; } ;
struct TYPE_7__ {int val; } ;
struct TYPE_6__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int*,int) ; 
 TYPE_5__* sensor_data ; 

__attribute__((used)) static void setawb_n_RGB(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 all_gain_reg[8] = {
		0x87, 0x00, 0x88, 0x00, 0x89, 0x00, 0x80, 0x00 };
	s32 red_gain, blue_gain, green_gain;

	green_gain = sd->gain->val;

	red_gain = green_gain + sd->red_balance->val;
	if (red_gain > 0x40)
		red_gain = 0x40;
	else if (red_gain < 0x10)
		red_gain = 0x10;

	blue_gain = green_gain + sd->blue_balance->val;
	if (blue_gain > 0x40)
		blue_gain = 0x40;
	else if (blue_gain < 0x10)
		blue_gain = 0x10;

	all_gain_reg[1] = red_gain;
	all_gain_reg[3] = blue_gain;
	all_gain_reg[5] = green_gain;
	all_gain_reg[7] = sensor_data[sd->sensor].reg80;
	if (!sd->awb->val)
		all_gain_reg[7] &= ~0x04; /* AWB off */

	reg_w_buf(gspca_dev, all_gain_reg, sizeof all_gain_reg);
}