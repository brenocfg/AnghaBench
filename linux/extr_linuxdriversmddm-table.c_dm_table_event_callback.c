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
struct dm_table {void (* event_fn ) (void*) ;void* event_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  _event_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dm_table_event_callback(struct dm_table *t,
			     void (*fn)(void *), void *context)
{
	mutex_lock(&_event_lock);
	t->event_fn = fn;
	t->event_context = context;
	mutex_unlock(&_event_lock);
}