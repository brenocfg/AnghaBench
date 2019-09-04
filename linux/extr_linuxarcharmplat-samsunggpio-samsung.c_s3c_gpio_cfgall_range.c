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
typedef  int /*<<< orphan*/  samsung_gpio_pull_t ;

/* Variables and functions */
 int s3c_gpio_cfgpin (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  s3c_gpio_setpull (unsigned int,int /*<<< orphan*/ ) ; 

int s3c_gpio_cfgall_range(unsigned int start, unsigned int nr,
			  unsigned int cfg, samsung_gpio_pull_t pull)
{
	int ret;

	for (; nr > 0; nr--, start++) {
		s3c_gpio_setpull(start, pull);
		ret = s3c_gpio_cfgpin(start, cfg);
		if (ret != 0)
			return ret;
	}

	return 0;
}