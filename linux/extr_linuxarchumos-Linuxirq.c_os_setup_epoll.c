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

/* Variables and functions */
 int /*<<< orphan*/  MAX_EPOLL_EVENTS ; 
 int epoll_create (int /*<<< orphan*/ ) ; 
 int epollfd ; 

int os_setup_epoll(void)
{
	epollfd = epoll_create(MAX_EPOLL_EVENTS);
	return epollfd;
}