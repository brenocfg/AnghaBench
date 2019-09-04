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
struct hwrng {int /*<<< orphan*/  cleanup_done; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ cur_rng_set_by_user ; 
 struct hwrng* current_rng ; 
 int /*<<< orphan*/  drop_current_rng () ; 
 int enable_best_rng () ; 
 scalar_t__ hwrng_fill ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rng_list ; 
 int /*<<< orphan*/  rng_mutex ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void hwrng_unregister(struct hwrng *rng)
{
	int err;

	mutex_lock(&rng_mutex);

	list_del(&rng->list);
	if (current_rng == rng) {
		err = enable_best_rng();
		if (err) {
			drop_current_rng();
			cur_rng_set_by_user = 0;
		}
	}

	if (list_empty(&rng_list)) {
		mutex_unlock(&rng_mutex);
		if (hwrng_fill)
			kthread_stop(hwrng_fill);
	} else
		mutex_unlock(&rng_mutex);

	wait_for_completion(&rng->cleanup_done);
}