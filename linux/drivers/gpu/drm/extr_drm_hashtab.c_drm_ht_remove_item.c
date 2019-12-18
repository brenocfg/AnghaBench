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
struct drm_open_hash {int dummy; } ;
struct drm_hash_item {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 

int drm_ht_remove_item(struct drm_open_hash *ht, struct drm_hash_item *item)
{
	hlist_del_init_rcu(&item->head);
	return 0;
}