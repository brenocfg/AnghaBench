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

/* Variables and functions */
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int const*,int) ; 

__attribute__((used)) static void setwb(struct gspca_dev *gspca_dev)
{
/*fixme:to do - valid when reg d1 = 0x1c - (reg16 + reg15 = 0xa3)*/
	static const u8 data[2] = {0x00, 0x00};

	i2c_write(gspca_dev, 0x16, &data[0], 1);
	i2c_write(gspca_dev, 0x18, &data[1], 1);
}