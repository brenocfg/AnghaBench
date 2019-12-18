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
struct ubi_wl_entry {int dummy; } ;
struct ubi_fm_pool {scalar_t__ used; scalar_t__ size; int* pebs; } ;
struct ubi_device {int fm_work_scheduled; struct ubi_wl_entry** lookuptbl; int /*<<< orphan*/  fm_work; int /*<<< orphan*/  fm_eba_sem; struct ubi_fm_pool fm_wl_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ubi_wl_entry *get_peb_for_wl(struct ubi_device *ubi)
{
	struct ubi_fm_pool *pool = &ubi->fm_wl_pool;
	int pnum;

	ubi_assert(rwsem_is_locked(&ubi->fm_eba_sem));

	if (pool->used == pool->size) {
		/* We cannot update the fastmap here because this
		 * function is called in atomic context.
		 * Let's fail here and refill/update it as soon as possible. */
		if (!ubi->fm_work_scheduled) {
			ubi->fm_work_scheduled = 1;
			schedule_work(&ubi->fm_work);
		}
		return NULL;
	}

	pnum = pool->pebs[pool->used++];
	return ubi->lookuptbl[pnum];
}