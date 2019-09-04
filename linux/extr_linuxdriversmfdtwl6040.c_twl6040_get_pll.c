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
struct twl6040 {int pll; scalar_t__ power_count; } ;

/* Variables and functions */
 int ENODEV ; 

int twl6040_get_pll(struct twl6040 *twl6040)
{
	if (twl6040->power_count)
		return twl6040->pll;
	else
		return -ENODEV;
}