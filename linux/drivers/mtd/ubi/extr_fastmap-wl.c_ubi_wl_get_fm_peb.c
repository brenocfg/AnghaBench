#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rb; } ;
struct ubi_wl_entry {TYPE_1__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  rb_node; } ;
struct ubi_device {int free_count; int beb_rsvd_pebs; TYPE_2__ free; } ;

/* Variables and functions */
 struct ubi_wl_entry* find_anchor_wl_entry (TYPE_2__*) ; 
 struct ubi_wl_entry* find_mean_wl_entry (struct ubi_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  self_check_in_wl_tree (struct ubi_device*,struct ubi_wl_entry*,TYPE_2__*) ; 

struct ubi_wl_entry *ubi_wl_get_fm_peb(struct ubi_device *ubi, int anchor)
{
	struct ubi_wl_entry *e = NULL;

	if (!ubi->free.rb_node || (ubi->free_count - ubi->beb_rsvd_pebs < 1))
		goto out;

	if (anchor)
		e = find_anchor_wl_entry(&ubi->free);
	else
		e = find_mean_wl_entry(ubi, &ubi->free);

	if (!e)
		goto out;

	self_check_in_wl_tree(ubi, e, &ubi->free);

	/* remove it from the free list,
	 * the wl subsystem does no longer know this erase block */
	rb_erase(&e->u.rb, &ubi->free);
	ubi->free_count--;
out:
	return e;
}