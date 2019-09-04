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
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int os_set_exec_close(int fd)
{
	int err;

	CATCH_EINTR(err = fcntl(fd, F_SETFD, FD_CLOEXEC));

	if (err < 0)
		return -errno;
	return err;
}