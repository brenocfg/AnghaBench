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
struct TYPE_2__ {scalar_t__ refcount; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __erst_record_id_cache_compact () ; 
 int erst_disable ; 
 TYPE_1__ erst_record_id_cache ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void erst_get_record_id_end(void)
{
	/*
	 * erst_disable != 0 should be detected by invoker via the
	 * return value of erst_get_record_id_begin/next, so this
	 * function should not be called for erst_disable != 0.
	 */
	BUG_ON(erst_disable);

	mutex_lock(&erst_record_id_cache.lock);
	erst_record_id_cache.refcount--;
	BUG_ON(erst_record_id_cache.refcount < 0);
	__erst_record_id_cache_compact();
	mutex_unlock(&erst_record_id_cache.lock);
}