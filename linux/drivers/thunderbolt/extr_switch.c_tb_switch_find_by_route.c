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
typedef  scalar_t__ u64 ;
struct tb_switch {int dummy; } ;
struct tb_sw_lookup {scalar_t__ route; struct tb* tb; } ;
struct tb {int /*<<< orphan*/  root_switch; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  lookup ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tb_sw_lookup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tb_sw_lookup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tb_bus_type ; 
 struct tb_switch* tb_switch_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_switch_match ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

struct tb_switch *tb_switch_find_by_route(struct tb *tb, u64 route)
{
	struct tb_sw_lookup lookup;
	struct device *dev;

	if (!route)
		return tb_switch_get(tb->root_switch);

	memset(&lookup, 0, sizeof(lookup));
	lookup.tb = tb;
	lookup.route = route;

	dev = bus_find_device(&tb_bus_type, NULL, &lookup, tb_switch_match);
	if (dev)
		return tb_to_switch(dev);

	return NULL;
}