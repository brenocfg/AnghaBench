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
struct ubi_fm_pool {scalar_t__ used; scalar_t__ size; int* pebs; } ;
struct ubi_device {int /*<<< orphan*/  wl_lock; int /*<<< orphan*/ * lookuptbl; int /*<<< orphan*/  fm_eba_sem; struct ubi_fm_pool fm_wl_pool; struct ubi_fm_pool fm_pool; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int produce_free_peb (struct ubi_device*) ; 
 int /*<<< orphan*/  prot_queue_add (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*,int) ; 
 int ubi_update_fastmap (struct ubi_device*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ubi_wl_get_peb(struct ubi_device *ubi)
{
	int ret, attempts = 0;
	struct ubi_fm_pool *pool = &ubi->fm_pool;
	struct ubi_fm_pool *wl_pool = &ubi->fm_wl_pool;

again:
	down_read(&ubi->fm_eba_sem);
	spin_lock(&ubi->wl_lock);

	/* We check here also for the WL pool because at this point we can
	 * refill the WL pool synchronous. */
	if (pool->used == pool->size || wl_pool->used == wl_pool->size) {
		spin_unlock(&ubi->wl_lock);
		up_read(&ubi->fm_eba_sem);
		ret = ubi_update_fastmap(ubi);
		if (ret) {
			ubi_msg(ubi, "Unable to write a new fastmap: %i", ret);
			down_read(&ubi->fm_eba_sem);
			return -ENOSPC;
		}
		down_read(&ubi->fm_eba_sem);
		spin_lock(&ubi->wl_lock);
	}

	if (pool->used == pool->size) {
		spin_unlock(&ubi->wl_lock);
		attempts++;
		if (attempts == 10) {
			ubi_err(ubi, "Unable to get a free PEB from user WL pool");
			ret = -ENOSPC;
			goto out;
		}
		up_read(&ubi->fm_eba_sem);
		ret = produce_free_peb(ubi);
		if (ret < 0) {
			down_read(&ubi->fm_eba_sem);
			goto out;
		}
		goto again;
	}

	ubi_assert(pool->used < pool->size);
	ret = pool->pebs[pool->used++];
	prot_queue_add(ubi, ubi->lookuptbl[ret]);
	spin_unlock(&ubi->wl_lock);
out:
	return ret;
}