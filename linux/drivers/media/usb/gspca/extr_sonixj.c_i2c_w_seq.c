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
typedef  scalar_t__ u8 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ const DELAY ; 
 int /*<<< orphan*/  i2c_w8 (struct gspca_dev*,scalar_t__ const*) ; 
 int /*<<< orphan*/  msleep (scalar_t__ const) ; 

__attribute__((used)) static void i2c_w_seq(struct gspca_dev *gspca_dev,
			const u8 (*data)[8])
{
	while ((*data)[0] != 0) {
		if ((*data)[0] != DELAY)
			i2c_w8(gspca_dev, *data);
		else
			msleep((*data)[1]);
		data++;
	}
}