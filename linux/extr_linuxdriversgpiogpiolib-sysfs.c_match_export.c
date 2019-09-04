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
struct gpiod_data {void const* desc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct gpiod_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int match_export(struct device *dev, const void *desc)
{
	struct gpiod_data *data = dev_get_drvdata(dev);

	return data->desc == desc;
}