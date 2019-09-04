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
struct twl6040 {unsigned int sysclk_rate; } ;

/* Variables and functions */

unsigned int twl6040_get_sysclk(struct twl6040 *twl6040)
{
	return twl6040->sysclk_rate;
}