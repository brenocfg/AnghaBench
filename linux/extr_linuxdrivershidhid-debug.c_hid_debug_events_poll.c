#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hid_debug_list {TYPE_1__* hdev; int /*<<< orphan*/  hid_debug_fifo; } ;
struct file {struct hid_debug_list* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  debug; int /*<<< orphan*/  debug_wait; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t hid_debug_events_poll(struct file *file, poll_table *wait)
{
	struct hid_debug_list *list = file->private_data;

	poll_wait(file, &list->hdev->debug_wait, wait);
	if (!kfifo_is_empty(&list->hid_debug_fifo))
		return EPOLLIN | EPOLLRDNORM;
	if (!list->hdev->debug)
		return EPOLLERR | EPOLLHUP;
	return 0;
}