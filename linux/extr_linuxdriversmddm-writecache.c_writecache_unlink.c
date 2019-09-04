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
struct wc_entry {int /*<<< orphan*/  rb_node; int /*<<< orphan*/  lru; } ;
struct dm_writecache {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void writecache_unlink(struct dm_writecache *wc, struct wc_entry *e)
{
	list_del(&e->lru);
	rb_erase(&e->rb_node, &wc->tree);
}