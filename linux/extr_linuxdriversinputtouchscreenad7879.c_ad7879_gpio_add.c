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
struct ad7879_platform_data {int dummy; } ;
struct ad7879 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ad7879_gpio_add(struct ad7879 *ts,
			   const struct ad7879_platform_data *pdata)
{
	return 0;
}