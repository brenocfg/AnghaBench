#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache {int level; TYPE_1__* ofnode; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void do_subsidiary_caches_debugcheck(struct cache *cache)
{
	WARN_ON_ONCE(cache->level != 1);
	WARN_ON_ONCE(strcmp(cache->ofnode->type, "cpu"));
}