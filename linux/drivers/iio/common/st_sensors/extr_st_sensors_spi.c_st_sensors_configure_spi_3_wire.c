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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ value; scalar_t__ addr; } ;
struct st_sensor_settings {TYPE_1__ sim; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int spi_write (struct spi_device*,scalar_t__*,int) ; 

__attribute__((used)) static int st_sensors_configure_spi_3_wire(struct spi_device *spi,
					   struct st_sensor_settings *settings)
{
	if (settings->sim.addr) {
		u8 buffer[] = {
			settings->sim.addr,
			settings->sim.value
		};

		return spi_write(spi, buffer, 2);
	}

	return 0;
}