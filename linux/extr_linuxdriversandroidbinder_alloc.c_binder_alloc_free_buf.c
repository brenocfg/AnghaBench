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
struct binder_buffer {int dummy; } ;
struct binder_alloc {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_free_buf_locked (struct binder_alloc*,struct binder_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void binder_alloc_free_buf(struct binder_alloc *alloc,
			    struct binder_buffer *buffer)
{
	mutex_lock(&alloc->mutex);
	binder_free_buf_locked(alloc, buffer);
	mutex_unlock(&alloc->mutex);
}