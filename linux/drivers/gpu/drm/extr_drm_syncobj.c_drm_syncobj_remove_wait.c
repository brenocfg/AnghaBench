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
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct syncobj_wait_entry {TYPE_1__ node; } ;
struct drm_syncobj {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_syncobj_remove_wait(struct drm_syncobj *syncobj,
				    struct syncobj_wait_entry *wait)
{
	if (!wait->node.next)
		return;

	spin_lock(&syncobj->lock);
	list_del_init(&wait->node);
	spin_unlock(&syncobj->lock);
}