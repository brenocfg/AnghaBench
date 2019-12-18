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
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_destroy_port (struct serio*) ; 
 int /*<<< orphan*/  serio_disconnect_port (struct serio*) ; 
 int /*<<< orphan*/  serio_mutex ; 

void serio_unregister_port(struct serio *serio)
{
	mutex_lock(&serio_mutex);
	serio_disconnect_port(serio);
	serio_destroy_port(serio);
	mutex_unlock(&serio_mutex);
}