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
struct vmw_cmdbuf_man {int /*<<< orphan*/  cur_mutex; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmw_cmdbuf_cur_lock(struct vmw_cmdbuf_man *man, bool interruptible)
{
	if (interruptible) {
		if (mutex_lock_interruptible(&man->cur_mutex))
			return -ERESTARTSYS;
	} else {
		mutex_lock(&man->cur_mutex);
	}

	return 0;
}