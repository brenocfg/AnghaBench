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
struct ec_event_queue {int capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  entries ; 
 struct ec_event_queue* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct ec_event_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ec_event_queue *event_queue_new(int capacity)
{
	struct ec_event_queue *q;

	q = kzalloc(struct_size(q, entries, capacity), GFP_KERNEL);
	if (!q)
		return NULL;

	q->capacity = capacity;

	return q;
}