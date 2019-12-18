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
struct cache_set {unsigned int devices_max_used; int /*<<< orphan*/  caching; struct bcache_device** devices; } ;
struct bcache_device {unsigned int id; struct cache_set* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  closure_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcache_device_attach(struct bcache_device *d, struct cache_set *c,
				 unsigned int id)
{
	d->id = id;
	d->c = c;
	c->devices[id] = d;

	if (id >= c->devices_max_used)
		c->devices_max_used = id + 1;

	closure_get(&c->caching);
}