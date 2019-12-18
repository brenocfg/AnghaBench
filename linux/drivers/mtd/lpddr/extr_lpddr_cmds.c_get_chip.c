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
struct map_info {int dummy; } ;
struct flchip_shared {int /*<<< orphan*/  lock; struct flchip* erasing; struct flchip* writing; } ;
struct flchip {scalar_t__ state; int oldstate; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wq; struct flchip_shared* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int FL_ERASING ; 
 scalar_t__ FL_SYNCING ; 
 int FL_WRITING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int chip_ready (struct map_info*,struct flchip*,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_chip (struct map_info*,struct flchip*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int get_chip(struct map_info *map, struct flchip *chip, int mode)
{
	int ret;
	DECLARE_WAITQUEUE(wait, current);

 retry:
	if (chip->priv && (mode == FL_WRITING || mode == FL_ERASING)
		&& chip->state != FL_SYNCING) {
		/*
		 * OK. We have possibility for contension on the write/erase
		 * operations which are global to the real chip and not per
		 * partition.  So let's fight it over in the partition which
		 * currently has authority on the operation.
		 *
		 * The rules are as follows:
		 *
		 * - any write operation must own shared->writing.
		 *
		 * - any erase operation must own _both_ shared->writing and
		 *   shared->erasing.
		 *
		 * - contension arbitration is handled in the owner's context.
		 *
		 * The 'shared' struct can be read and/or written only when
		 * its lock is taken.
		 */
		struct flchip_shared *shared = chip->priv;
		struct flchip *contender;
		mutex_lock(&shared->lock);
		contender = shared->writing;
		if (contender && contender != chip) {
			/*
			 * The engine to perform desired operation on this
			 * partition is already in use by someone else.
			 * Let's fight over it in the context of the chip
			 * currently using it.  If it is possible to suspend,
			 * that other partition will do just that, otherwise
			 * it'll happily send us to sleep.  In any case, when
			 * get_chip returns success we're clear to go ahead.
			 */
			ret = mutex_trylock(&contender->mutex);
			mutex_unlock(&shared->lock);
			if (!ret)
				goto retry;
			mutex_unlock(&chip->mutex);
			ret = chip_ready(map, contender, mode);
			mutex_lock(&chip->mutex);

			if (ret == -EAGAIN) {
				mutex_unlock(&contender->mutex);
				goto retry;
			}
			if (ret) {
				mutex_unlock(&contender->mutex);
				return ret;
			}
			mutex_lock(&shared->lock);

			/* We should not own chip if it is already in FL_SYNCING
			 * state. Put contender and retry. */
			if (chip->state == FL_SYNCING) {
				put_chip(map, contender);
				mutex_unlock(&contender->mutex);
				goto retry;
			}
			mutex_unlock(&contender->mutex);
		}

		/* Check if we have suspended erase on this chip.
		   Must sleep in such a case. */
		if (mode == FL_ERASING && shared->erasing
		    && shared->erasing->oldstate == FL_ERASING) {
			mutex_unlock(&shared->lock);
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unlock(&chip->mutex);
			schedule();
			remove_wait_queue(&chip->wq, &wait);
			mutex_lock(&chip->mutex);
			goto retry;
		}

		/* We now own it */
		shared->writing = chip;
		if (mode == FL_ERASING)
			shared->erasing = chip;
		mutex_unlock(&shared->lock);
	}

	ret = chip_ready(map, chip, mode);
	if (ret == -EAGAIN)
		goto retry;

	return ret;
}