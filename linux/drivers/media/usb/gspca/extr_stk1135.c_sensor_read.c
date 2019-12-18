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
 int sensor_read_16 (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sensor_set_page (struct gspca_dev*,int) ; 

__attribute__((used)) static u16 sensor_read(struct gspca_dev *gspca_dev, u16 reg)
{
	sensor_set_page(gspca_dev, reg >> 8);
	return sensor_read_16(gspca_dev, reg & 0xff);
}