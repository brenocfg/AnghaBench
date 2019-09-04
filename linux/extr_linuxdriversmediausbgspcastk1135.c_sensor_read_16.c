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
 int sensor_read_8 (struct gspca_dev*,int) ; 

__attribute__((used)) static u16 sensor_read_16(struct gspca_dev *gspca_dev, u8 addr)
{
	return (sensor_read_8(gspca_dev, addr) << 8) |
		sensor_read_8(gspca_dev, 0xf1);
}