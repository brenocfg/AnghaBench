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
typedef  int /*<<< orphan*/  nvram_var ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENOENT ; 
 int NVRAM_MAX_GPIO_ENTRIES ; 
 int NVRAM_MAX_GPIO_VALUE_LEN ; 
 int bcm47xx_nvram_getenv (char*,char*,int) ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int bcm47xx_nvram_gpio_pin(const char *name)
{
	int i, err;
	char nvram_var[] = "gpioXX";
	char buf[NVRAM_MAX_GPIO_VALUE_LEN];

	/* TODO: Optimize it to don't call getenv so many times */
	for (i = 0; i < NVRAM_MAX_GPIO_ENTRIES; i++) {
		err = snprintf(nvram_var, sizeof(nvram_var), "gpio%i", i);
		if (err <= 0)
			continue;
		err = bcm47xx_nvram_getenv(nvram_var, buf, sizeof(buf));
		if (err <= 0)
			continue;
		if (!strcmp(name, buf))
			return i;
	}
	return -ENOENT;
}