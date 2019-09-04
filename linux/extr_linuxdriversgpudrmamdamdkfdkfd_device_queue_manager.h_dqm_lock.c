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
struct device_queue_manager {int /*<<< orphan*/  saved_flags; int /*<<< orphan*/  lock_hidden; } ;

/* Variables and functions */
 int /*<<< orphan*/  memalloc_nofs_save () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dqm_lock(struct device_queue_manager *dqm)
{
	mutex_lock(&dqm->lock_hidden);
	dqm->saved_flags = memalloc_nofs_save();
}