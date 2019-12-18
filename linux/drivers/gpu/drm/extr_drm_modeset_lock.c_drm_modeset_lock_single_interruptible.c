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
struct drm_modeset_lock {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ww_mutex_lock_interruptible (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_modeset_lock_single_interruptible(struct drm_modeset_lock *lock)
{
	return ww_mutex_lock_interruptible(&lock->mutex, NULL);
}