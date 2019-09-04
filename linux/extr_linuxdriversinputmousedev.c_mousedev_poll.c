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
struct mousedev_client {scalar_t__ buffer; scalar_t__ ready; struct mousedev* mousedev; } ;
struct mousedev {scalar_t__ exist; int /*<<< orphan*/  wait; } ;
struct file {struct mousedev_client* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t mousedev_poll(struct file *file, poll_table *wait)
{
	struct mousedev_client *client = file->private_data;
	struct mousedev *mousedev = client->mousedev;
	__poll_t mask;

	poll_wait(file, &mousedev->wait, wait);

	mask = mousedev->exist ? EPOLLOUT | EPOLLWRNORM : EPOLLHUP | EPOLLERR;
	if (client->ready || client->buffer)
		mask |= EPOLLIN | EPOLLRDNORM;

	return mask;
}