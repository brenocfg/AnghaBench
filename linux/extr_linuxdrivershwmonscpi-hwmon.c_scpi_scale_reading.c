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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {size_t class; } ;
struct sensor_data {int /*<<< orphan*/  scale; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scpi_scale ; 

__attribute__((used)) static void scpi_scale_reading(u64 *value, struct sensor_data *sensor)
{
	if (scpi_scale[sensor->info.class] != sensor->scale) {
		*value *= scpi_scale[sensor->info.class];
		do_div(*value, sensor->scale);
	}
}