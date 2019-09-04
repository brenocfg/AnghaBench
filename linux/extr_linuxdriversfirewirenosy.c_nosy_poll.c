#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {struct client* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  wait; } ;
struct client {TYPE_1__* lynx; TYPE_2__ buffer; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_3__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t
nosy_poll(struct file *file, poll_table *pt)
{
	struct client *client = file->private_data;
	__poll_t ret = 0;

	poll_wait(file, &client->buffer.wait, pt);

	if (atomic_read(&client->buffer.size) > 0)
		ret = EPOLLIN | EPOLLRDNORM;

	if (list_empty(&client->lynx->link))
		ret |= EPOLLHUP;

	return ret;
}