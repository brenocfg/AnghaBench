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
struct ubi_wl_entry {TYPE_1__ u; int /*<<< orphan*/  pnum; } ;
struct ubi_device {int peb_count; int /*<<< orphan*/  work_sem; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  free_count; int /*<<< orphan*/  free; int /*<<< orphan*/  scrub; int /*<<< orphan*/  used; struct ubi_wl_entry** lookuptbl; int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  peb_size; int /*<<< orphan*/  peb_buf; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int EUCLEAN ; 
 int UBI_IO_BITFLIPS ; 
 int /*<<< orphan*/  UBI_UNKNOWN ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int ensure_wear_leveling (struct ubi_device*,int) ; 
 scalar_t__ in_pq (struct ubi_device*,struct ubi_wl_entry*) ; 
 scalar_t__ in_wl_tree (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prot_queue_del (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int schedule_erase (struct ubi_device*,struct ubi_wl_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  scrub_possible (struct ubi_device*,struct ubi_wl_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ubi_io_read (struct ubi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_tree_add (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 

int ubi_bitflip_check(struct ubi_device *ubi, int pnum, int force)
{
	int err = 0;
	struct ubi_wl_entry *e;

	if (pnum < 0 || pnum >= ubi->peb_count) {
		err = -EINVAL;
		goto out;
	}

	/*
	 * Pause all parallel work, otherwise it can happen that the
	 * erase worker frees a wl entry under us.
	 */
	down_write(&ubi->work_sem);

	/*
	 * Make sure that the wl entry does not change state while
	 * inspecting it.
	 */
	spin_lock(&ubi->wl_lock);
	e = ubi->lookuptbl[pnum];
	if (!e) {
		spin_unlock(&ubi->wl_lock);
		err = -ENOENT;
		goto out_resume;
	}

	/*
	 * Does it make sense to check this PEB?
	 */
	if (!scrub_possible(ubi, e)) {
		spin_unlock(&ubi->wl_lock);
		err = -EBUSY;
		goto out_resume;
	}
	spin_unlock(&ubi->wl_lock);

	if (!force) {
		mutex_lock(&ubi->buf_mutex);
		err = ubi_io_read(ubi, ubi->peb_buf, pnum, 0, ubi->peb_size);
		mutex_unlock(&ubi->buf_mutex);
	}

	if (force || err == UBI_IO_BITFLIPS) {
		/*
		 * Okay, bit flip happened, let's figure out what we can do.
		 */
		spin_lock(&ubi->wl_lock);

		/*
		 * Recheck. We released wl_lock, UBI might have killed the
		 * wl entry under us.
		 */
		e = ubi->lookuptbl[pnum];
		if (!e) {
			spin_unlock(&ubi->wl_lock);
			err = -ENOENT;
			goto out_resume;
		}

		/*
		 * Need to re-check state
		 */
		if (!scrub_possible(ubi, e)) {
			spin_unlock(&ubi->wl_lock);
			err = -EBUSY;
			goto out_resume;
		}

		if (in_pq(ubi, e)) {
			prot_queue_del(ubi, e->pnum);
			wl_tree_add(e, &ubi->scrub);
			spin_unlock(&ubi->wl_lock);

			err = ensure_wear_leveling(ubi, 1);
		} else if (in_wl_tree(e, &ubi->used)) {
			rb_erase(&e->u.rb, &ubi->used);
			wl_tree_add(e, &ubi->scrub);
			spin_unlock(&ubi->wl_lock);

			err = ensure_wear_leveling(ubi, 1);
		} else if (in_wl_tree(e, &ubi->free)) {
			rb_erase(&e->u.rb, &ubi->free);
			ubi->free_count--;
			spin_unlock(&ubi->wl_lock);

			/*
			 * This PEB is empty we can schedule it for
			 * erasure right away. No wear leveling needed.
			 */
			err = schedule_erase(ubi, e, UBI_UNKNOWN, UBI_UNKNOWN,
					     force ? 0 : 1, true);
		} else {
			spin_unlock(&ubi->wl_lock);
			err = -EAGAIN;
		}

		if (!err && !force)
			err = -EUCLEAN;
	} else {
		err = 0;
	}

out_resume:
	up_write(&ubi->work_sem);
out:

	return err;
}