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
struct sd {scalar_t__ flip_status; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  sensor_write_mask (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void setvflip(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->flip_status)
		val = !val;
	sensor_write_mask(gspca_dev, 0x020, val ? 0x0001 : 0x0000 , 0x0001);
}