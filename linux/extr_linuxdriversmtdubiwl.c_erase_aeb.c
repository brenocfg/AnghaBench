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
struct ubi_wl_entry {size_t pnum; int /*<<< orphan*/  ec; } ;
struct ubi_device {int /*<<< orphan*/  free_count; int /*<<< orphan*/  free; struct ubi_wl_entry** lookuptbl; } ;
struct ubi_ainf_peb {size_t pnum; int /*<<< orphan*/  lnum; int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ubi_wl_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int schedule_erase (struct ubi_device*,struct ubi_wl_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sync_erase (struct ubi_device*,struct ubi_wl_entry*,int) ; 
 int /*<<< orphan*/  ubi_wl_entry_slab ; 
 int /*<<< orphan*/  wl_entry_destroy (struct ubi_device*,struct ubi_wl_entry*) ; 
 int /*<<< orphan*/  wl_tree_add (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int erase_aeb(struct ubi_device *ubi, struct ubi_ainf_peb *aeb, bool sync)
{
	struct ubi_wl_entry *e;
	int err;

	e = kmem_cache_alloc(ubi_wl_entry_slab, GFP_KERNEL);
	if (!e)
		return -ENOMEM;

	e->pnum = aeb->pnum;
	e->ec = aeb->ec;
	ubi->lookuptbl[e->pnum] = e;

	if (sync) {
		err = sync_erase(ubi, e, false);
		if (err)
			goto out_free;

		wl_tree_add(e, &ubi->free);
		ubi->free_count++;
	} else {
		err = schedule_erase(ubi, e, aeb->vol_id, aeb->lnum, 0, false);
		if (err)
			goto out_free;
	}

	return 0;

out_free:
	wl_entry_destroy(ubi, e);

	return err;
}