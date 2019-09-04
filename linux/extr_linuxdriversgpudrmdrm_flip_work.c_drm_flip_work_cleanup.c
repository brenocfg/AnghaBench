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
struct drm_flip_work {int /*<<< orphan*/  commited; int /*<<< orphan*/  queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void drm_flip_work_cleanup(struct drm_flip_work *work)
{
	WARN_ON(!list_empty(&work->queued) || !list_empty(&work->commited));
}