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

/* Variables and functions */
 int /*<<< orphan*/  buffer_mutex ; 
 scalar_t__ buffer_pos ; 
 int /*<<< orphan*/ * event_buffer ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void free_event_buffer(void)
{
	mutex_lock(&buffer_mutex);
	vfree(event_buffer);
	buffer_pos = 0;
	event_buffer = NULL;
	mutex_unlock(&buffer_mutex);
}