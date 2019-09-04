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
struct mmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int EAGAIN ; 
 int errno ; 
 int recvmmsg (int,struct mmsghdr*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int uml_vector_recvmmsg(
	int fd,
	void *msgvec,
	unsigned int vlen,
	unsigned int flags)
{
	int n;

	CATCH_EINTR(
		n = recvmmsg(fd, (struct mmsghdr *) msgvec, vlen, flags, 0));
	if ((n < 0) && (errno == EAGAIN))
		return 0;
	if (n >= 0)
		return n;
	else
		return -errno;
}