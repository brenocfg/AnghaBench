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
struct drm_modeset_lock {int /*<<< orphan*/  head; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crtc_ww_class ; 
 int /*<<< orphan*/  ww_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void drm_modeset_lock_init(struct drm_modeset_lock *lock)
{
	ww_mutex_init(&lock->mutex, &crtc_ww_class);
	INIT_LIST_HEAD(&lock->head);
}