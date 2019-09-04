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
struct uuid_entry {int /*<<< orphan*/  uuid; } ;
struct cache_set {int nr_uuids; struct uuid_entry* uuids; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct uuid_entry *uuid_find(struct cache_set *c, const char *uuid)
{
	struct uuid_entry *u;

	for (u = c->uuids;
	     u < c->uuids + c->nr_uuids; u++)
		if (!memcmp(u->uuid, uuid, 16))
			return u;

	return NULL;
}