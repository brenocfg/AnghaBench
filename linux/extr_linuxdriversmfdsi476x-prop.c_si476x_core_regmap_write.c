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
 int si476x_core_cmd_set_property (void*,unsigned int,unsigned int) ; 

__attribute__((used)) static int si476x_core_regmap_write(void *context, unsigned int reg,
				    unsigned int val)
{
	return si476x_core_cmd_set_property(context, reg, val);
}