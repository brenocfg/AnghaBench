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
struct roccat_reader {scalar_t__ cbuf_start; TYPE_1__* device; } ;
struct file {struct roccat_reader* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {scalar_t__ cbuf_end; int /*<<< orphan*/  exist; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t roccat_poll(struct file *file, poll_table *wait)
{
	struct roccat_reader *reader = file->private_data;
	poll_wait(file, &reader->device->wait, wait);
	if (reader->cbuf_start != reader->device->cbuf_end)
		return EPOLLIN | EPOLLRDNORM;
	if (!reader->device->exist)
		return EPOLLERR | EPOLLHUP;
	return 0;
}