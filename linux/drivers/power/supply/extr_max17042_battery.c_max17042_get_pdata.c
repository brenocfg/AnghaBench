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
struct max17042_platform_data {int dummy; } ;
struct max17042_chip {TYPE_1__* client; } ;
struct device {struct max17042_platform_data* platform_data; scalar_t__ of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 struct max17042_platform_data* max17042_get_default_pdata (struct max17042_chip*) ; 
 struct max17042_platform_data* max17042_get_of_pdata (struct max17042_chip*) ; 

__attribute__((used)) static struct max17042_platform_data *
max17042_get_pdata(struct max17042_chip *chip)
{
	struct device *dev = &chip->client->dev;

#ifdef CONFIG_OF
	if (dev->of_node)
		return max17042_get_of_pdata(chip);
#endif
	if (dev->platform_data)
		return dev->platform_data;

	return max17042_get_default_pdata(chip);
}