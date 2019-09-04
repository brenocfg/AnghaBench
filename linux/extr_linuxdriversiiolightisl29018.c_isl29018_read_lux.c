#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int scale; int uscale; } ;
struct isl29018_chip {unsigned int calibscale; unsigned int ucalibscale; TYPE_1__ scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISL29018_CMD1_OPMODE_ALS_ONCE ; 
 int isl29018_read_sensor_input (struct isl29018_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl29018_read_lux(struct isl29018_chip *chip, int *lux)
{
	int lux_data;
	unsigned int data_x_range;

	lux_data = isl29018_read_sensor_input(chip,
					      ISL29018_CMD1_OPMODE_ALS_ONCE);
	if (lux_data < 0)
		return lux_data;

	data_x_range = lux_data * chip->scale.scale +
		       lux_data * chip->scale.uscale / 1000000;
	*lux = data_x_range * chip->calibscale +
	       data_x_range * chip->ucalibscale / 1000000;

	return 0;
}