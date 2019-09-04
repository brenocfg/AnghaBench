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
struct TYPE_2__ {int /*<<< orphan*/  rb; } ;
struct ubi_wl_entry {int /*<<< orphan*/  ec; int /*<<< orphan*/  pnum; TYPE_1__ u; } ;
struct ubi_device {int /*<<< orphan*/  free_count; int /*<<< orphan*/  free; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_wl (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ubi_wl_entry* find_mean_wl_entry (struct ubi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  self_check_in_wl_tree (struct ubi_device*,struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*) ; 

__attribute__((used)) static struct ubi_wl_entry *wl_get_wle(struct ubi_device *ubi)
{
	struct ubi_wl_entry *e;

	e = find_mean_wl_entry(ubi, &ubi->free);
	if (!e) {
		ubi_err(ubi, "no free eraseblocks");
		return NULL;
	}

	self_check_in_wl_tree(ubi, e, &ubi->free);

	/*
	 * Move the physical eraseblock to the protection queue where it will
	 * be protected from being moved for some time.
	 */
	rb_erase(&e->u.rb, &ubi->free);
	ubi->free_count--;
	dbg_wl("PEB %d EC %d", e->pnum, e->ec);

	return e;
}