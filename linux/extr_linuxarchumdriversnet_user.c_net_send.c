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
 int EAGAIN ; 
 int ENOTCONN ; 
 int errno ; 
 int send (int,void*,int,int /*<<< orphan*/ ) ; 

int net_send(int fd, void *buf, int len)
{
	int n;

	CATCH_EINTR(n = send(fd, buf, len, 0));
	if (n < 0) {
		if (errno == EAGAIN)
			return 0;
		return -errno;
	}
	else if (n == 0)
		return -ENOTCONN;
	return n;
}