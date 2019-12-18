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
typedef  int u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sensor_write_8 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sensor_write_16(struct gspca_dev *gspca_dev, u8 addr, u16 data)
{
	sensor_write_8(gspca_dev, addr, data >> 8);
	sensor_write_8(gspca_dev, 0xf1, data & 0xff);
}