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
struct list_head {int dummy; } ;
struct iowait {scalar_t__ priority; int /*<<< orphan*/  list; scalar_t__ starved_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static inline void iowait_queue(bool pkts_sent, struct iowait *w,
				struct list_head *wait_head)
{
	/*
	 * To play fair, insert the iowait at the tail of the wait queue if it
	 * has already sent some packets; Otherwise, put it at the head.
	 * However, if it has priority packets to send, also put it at the
	 * head.
	 */
	if (pkts_sent)
		w->starved_cnt = 0;
	else
		w->starved_cnt++;

	if (w->priority > 0 || !pkts_sent)
		list_add(&w->list, wait_head);
	else
		list_add_tail(&w->list, wait_head);
}