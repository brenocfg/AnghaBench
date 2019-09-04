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
struct uhid_device {scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  waitq; } ;
struct file {struct uhid_device* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t uhid_char_poll(struct file *file, poll_table *wait)
{
	struct uhid_device *uhid = file->private_data;

	poll_wait(file, &uhid->waitq, wait);

	if (uhid->head != uhid->tail)
		return EPOLLIN | EPOLLRDNORM;

	return 0;
}