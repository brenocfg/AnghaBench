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
struct ec_event_queue {int dummy; } ;
typedef  struct ec_event_queue ec_event ;

/* Variables and functions */
 struct ec_event_queue* event_queue_pop (struct ec_event_queue*) ; 
 int /*<<< orphan*/  kfree (struct ec_event_queue*) ; 

__attribute__((used)) static void event_queue_free(struct ec_event_queue *q)
{
	struct ec_event *event;

	while ((event = event_queue_pop(q)) != NULL)
		kfree(event);

	kfree(q);
}