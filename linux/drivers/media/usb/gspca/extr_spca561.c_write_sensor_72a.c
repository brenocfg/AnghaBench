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
struct gspca_dev {int dummy; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static void write_sensor_72a(struct gspca_dev *gspca_dev,
			    const __u16 (*sensor)[2])
{
	while ((*sensor)[0]) {
		i2c_write(gspca_dev, (*sensor)[1], (*sensor)[0]);
		sensor++;
	}
}