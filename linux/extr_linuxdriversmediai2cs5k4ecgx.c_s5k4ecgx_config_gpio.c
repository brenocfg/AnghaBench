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

/* Variables and functions */
 unsigned long GPIOF_OUT_INIT_HIGH ; 
 unsigned long GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  gpio_export (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int gpio_request_one (int,unsigned long,char const*) ; 

__attribute__((used)) static int s5k4ecgx_config_gpio(int nr, int val, const char *name)
{
	unsigned long flags = val ? GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW;
	int ret;

	if (!gpio_is_valid(nr))
		return 0;
	ret = gpio_request_one(nr, flags, name);
	if (!ret)
		gpio_export(nr, 0);

	return ret;
}