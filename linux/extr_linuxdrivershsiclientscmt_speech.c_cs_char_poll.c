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
struct file {struct cs_char* private_data; } ;
struct cs_char {int /*<<< orphan*/  lock; int /*<<< orphan*/  dataind_queue; int /*<<< orphan*/  chardev_queue; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 TYPE_1__ cs_char_data ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t cs_char_poll(struct file *file, poll_table *wait)
{
	struct cs_char *csdata = file->private_data;
	__poll_t ret = 0;

	poll_wait(file, &cs_char_data.wait, wait);
	spin_lock_bh(&csdata->lock);
	if (!list_empty(&csdata->chardev_queue))
		ret = EPOLLIN | EPOLLRDNORM;
	else if (!list_empty(&csdata->dataind_queue))
		ret = EPOLLIN | EPOLLRDNORM;
	spin_unlock_bh(&csdata->lock);

	return ret;
}