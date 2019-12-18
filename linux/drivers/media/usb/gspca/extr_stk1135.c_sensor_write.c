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
 int /*<<< orphan*/  sensor_set_page (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sensor_write_16 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sensor_write(struct gspca_dev *gspca_dev, u16 reg, u16 val)
{
	sensor_set_page(gspca_dev, reg >> 8);
	sensor_write_16(gspca_dev, reg & 0xff, val);
}