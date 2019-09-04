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
struct st_sensors_platform_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct st_sensors_platform_data *st_sensors_of_probe(struct device *dev,
		struct st_sensors_platform_data *defdata)
{
	return NULL;
}