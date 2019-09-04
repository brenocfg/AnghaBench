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
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int const*,int) ; 

__attribute__((used)) static void setautogain(struct gspca_dev *gspca_dev, s32 val)
{
	static const u8 data[2] = {0x28, 0x3c};

	i2c_write(gspca_dev, 0xd1, &data[val], 1);
}