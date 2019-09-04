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
struct drm_modeset_lock {int /*<<< orphan*/  mutex; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_modeset_unlock(struct drm_modeset_lock *lock)
{
	list_del_init(&lock->head);
	ww_mutex_unlock(&lock->mutex);
}