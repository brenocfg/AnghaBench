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
struct vmw_fence_manager {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vmw_fences_update (struct vmw_fence_manager*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void vmw_fences_update(struct vmw_fence_manager *fman)
{
	spin_lock(&fman->lock);
	__vmw_fences_update(fman);
	spin_unlock(&fman->lock);
}