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
struct property {scalar_t__ length; void const* value; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 scalar_t__ is_valid_ether_addr (void const*) ; 
 struct property* of_find_property (struct device_node*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const void *of_get_mac_addr(struct device_node *np, const char *name)
{
	struct property *pp = of_find_property(np, name, NULL);

	if (pp && pp->length == ETH_ALEN && is_valid_ether_addr(pp->value))
		return pp->value;
	return NULL;
}