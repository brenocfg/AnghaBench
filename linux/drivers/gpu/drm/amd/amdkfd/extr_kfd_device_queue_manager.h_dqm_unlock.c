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
struct device_queue_manager {int /*<<< orphan*/  lock_hidden; int /*<<< orphan*/  saved_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  memalloc_nofs_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dqm_unlock(struct device_queue_manager *dqm)
{
	memalloc_nofs_restore(dqm->saved_flags);
	mutex_unlock(&dqm->lock_hidden);
}