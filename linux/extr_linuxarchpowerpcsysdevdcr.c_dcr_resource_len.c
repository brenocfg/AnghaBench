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
typedef  unsigned int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned int* of_get_property (struct device_node const*,char*,unsigned int*) ; 

unsigned int dcr_resource_len(const struct device_node *np, unsigned int index)
{
	unsigned int ds;
	const u32 *dr = of_get_property(np, "dcr-reg", &ds);

	if (dr == NULL || ds & 1 || index >= (ds / 8))
		return 0;

	return dr[index * 2 + 1];
}