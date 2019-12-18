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
 int /*<<< orphan*/  SERIO_RECONNECT_SUBTREE ; 
 int /*<<< orphan*/  serio_queue_event (struct serio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void serio_reconnect(struct serio *serio)
{
	serio_queue_event(serio, NULL, SERIO_RECONNECT_SUBTREE);
}