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
struct ubi_wl_entry {int /*<<< orphan*/  pnum; TYPE_1__ u; } ;
struct ubi_device {int peb_count; int move_to_put; scalar_t__ erroneous_peb_count; int /*<<< orphan*/  fm_protect; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  used; int /*<<< orphan*/  erroneous; int /*<<< orphan*/  scrub; struct ubi_wl_entry* move_to; int /*<<< orphan*/  move_mutex; struct ubi_wl_entry* move_from; struct ubi_wl_entry** lookuptbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_wl (char*,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ in_wl_tree (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int prot_queue_del (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int schedule_erase (struct ubi_device*,struct ubi_wl_entry*,int,int,int,int) ; 
 int /*<<< orphan*/  self_check_in_wl_tree (struct ubi_device*,struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int) ; 
 int /*<<< orphan*/  ubi_ro_mode (struct ubi_device*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_tree_add (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 

int ubi_wl_put_peb(struct ubi_device *ubi, int vol_id, int lnum,
		   int pnum, int torture)
{
	int err;
	struct ubi_wl_entry *e;

	dbg_wl("PEB %d", pnum);
	ubi_assert(pnum >= 0);
	ubi_assert(pnum < ubi->peb_count);

	down_read(&ubi->fm_protect);

retry:
	spin_lock(&ubi->wl_lock);
	e = ubi->lookuptbl[pnum];
	if (e == ubi->move_from) {
		/*
		 * User is putting the physical eraseblock which was selected to
		 * be moved. It will be scheduled for erasure in the
		 * wear-leveling worker.
		 */
		dbg_wl("PEB %d is being moved, wait", pnum);
		spin_unlock(&ubi->wl_lock);

		/* Wait for the WL worker by taking the @ubi->move_mutex */
		mutex_lock(&ubi->move_mutex);
		mutex_unlock(&ubi->move_mutex);
		goto retry;
	} else if (e == ubi->move_to) {
		/*
		 * User is putting the physical eraseblock which was selected
		 * as the target the data is moved to. It may happen if the EBA
		 * sub-system already re-mapped the LEB in 'ubi_eba_copy_leb()'
		 * but the WL sub-system has not put the PEB to the "used" tree
		 * yet, but it is about to do this. So we just set a flag which
		 * will tell the WL worker that the PEB is not needed anymore
		 * and should be scheduled for erasure.
		 */
		dbg_wl("PEB %d is the target of data moving", pnum);
		ubi_assert(!ubi->move_to_put);
		ubi->move_to_put = 1;
		spin_unlock(&ubi->wl_lock);
		up_read(&ubi->fm_protect);
		return 0;
	} else {
		if (in_wl_tree(e, &ubi->used)) {
			self_check_in_wl_tree(ubi, e, &ubi->used);
			rb_erase(&e->u.rb, &ubi->used);
		} else if (in_wl_tree(e, &ubi->scrub)) {
			self_check_in_wl_tree(ubi, e, &ubi->scrub);
			rb_erase(&e->u.rb, &ubi->scrub);
		} else if (in_wl_tree(e, &ubi->erroneous)) {
			self_check_in_wl_tree(ubi, e, &ubi->erroneous);
			rb_erase(&e->u.rb, &ubi->erroneous);
			ubi->erroneous_peb_count -= 1;
			ubi_assert(ubi->erroneous_peb_count >= 0);
			/* Erroneous PEBs should be tortured */
			torture = 1;
		} else {
			err = prot_queue_del(ubi, e->pnum);
			if (err) {
				ubi_err(ubi, "PEB %d not found", pnum);
				ubi_ro_mode(ubi);
				spin_unlock(&ubi->wl_lock);
				up_read(&ubi->fm_protect);
				return err;
			}
		}
	}
	spin_unlock(&ubi->wl_lock);

	err = schedule_erase(ubi, e, vol_id, lnum, torture, false);
	if (err) {
		spin_lock(&ubi->wl_lock);
		wl_tree_add(e, &ubi->used);
		spin_unlock(&ubi->wl_lock);
	}

	up_read(&ubi->fm_protect);
	return err;
}