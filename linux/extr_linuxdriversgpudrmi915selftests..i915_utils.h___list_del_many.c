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
struct list_head {int /*<<< orphan*/  next; struct list_head* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct list_head*) ; 

__attribute__((used)) static inline void __list_del_many(struct list_head *head,
				   struct list_head *first)
{
	first->prev = head;
	WRITE_ONCE(head->next, first);
}