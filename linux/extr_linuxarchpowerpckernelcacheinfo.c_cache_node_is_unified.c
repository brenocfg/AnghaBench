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
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_get_property (struct device_node const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cache_node_is_unified(const struct device_node *np)
{
	return of_get_property(np, "cache-unified", NULL);
}