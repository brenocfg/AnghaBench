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
struct mapped_device {int /*<<< orphan*/  suspend_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_queue_flush (struct mapped_device*) ; 
 scalar_t__ dm_suspended_internally_md (struct mapped_device*) ; 
 scalar_t__ dm_suspended_md (struct mapped_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dm_internal_resume_fast(struct mapped_device *md)
{
	if (dm_suspended_md(md) || dm_suspended_internally_md(md))
		goto done;

	dm_queue_flush(md);

done:
	mutex_unlock(&md->suspend_lock);
}