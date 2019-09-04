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
struct epoll_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  epollfd ; 

int os_del_epoll_fd(int fd)
{
	struct epoll_event event;
	int result;
	/* This is quiet as we use this as IO ON/OFF - so it is often
	 * invoked on a non-existent fd
	 */
	result = epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);
	return result;
}