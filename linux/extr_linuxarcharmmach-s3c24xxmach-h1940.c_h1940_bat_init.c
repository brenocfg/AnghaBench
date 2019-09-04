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
 int /*<<< orphan*/  H1940_LATCH_SM803_ENABLE ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int h1940_bat_init(void)
{
	int ret;

	ret = gpio_request(H1940_LATCH_SM803_ENABLE, "h1940-charger-enable");
	if (ret)
		return ret;
	gpio_direction_output(H1940_LATCH_SM803_ENABLE, 0);

	return 0;

}