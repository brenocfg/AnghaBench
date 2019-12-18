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
struct userio_device {scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  waitq; } ;
struct file {struct userio_device* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t userio_char_poll(struct file *file, poll_table *wait)
{
	struct userio_device *userio = file->private_data;

	poll_wait(file, &userio->waitq, wait);

	if (userio->head != userio->tail)
		return EPOLLIN | EPOLLRDNORM;

	return 0;
}