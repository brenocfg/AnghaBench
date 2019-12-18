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
typedef  int u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int sensor_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sensor_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sensor_write_mask(struct gspca_dev *gspca_dev,
			u16 reg, u16 val, u16 mask)
{
	val = (sensor_read(gspca_dev, reg) & ~mask) | (val & mask);
	sensor_write(gspca_dev, reg, val);
}