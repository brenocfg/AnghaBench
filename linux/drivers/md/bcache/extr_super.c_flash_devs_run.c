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
struct uuid_entry {int dummy; } ;
struct cache_set {int nr_uuids; struct uuid_entry* uuids; } ;

/* Variables and functions */
 scalar_t__ UUID_FLASH_ONLY (struct uuid_entry*) ; 
 int flash_dev_run (struct cache_set*,struct uuid_entry*) ; 

__attribute__((used)) static int flash_devs_run(struct cache_set *c)
{
	int ret = 0;
	struct uuid_entry *u;

	for (u = c->uuids;
	     u < c->uuids + c->nr_uuids && !ret;
	     u++)
		if (UUID_FLASH_ONLY(u))
			ret = flash_dev_run(c, u);

	return ret;
}