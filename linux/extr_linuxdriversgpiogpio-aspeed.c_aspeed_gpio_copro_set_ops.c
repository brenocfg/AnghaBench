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
struct aspeed_gpio_copro_ops {int dummy; } ;

/* Variables and functions */
 void* copro_data ; 
 struct aspeed_gpio_copro_ops const* copro_ops ; 

int aspeed_gpio_copro_set_ops(const struct aspeed_gpio_copro_ops *ops, void *data)
{
	copro_data = data;
	copro_ops = ops;

	return 0;
}