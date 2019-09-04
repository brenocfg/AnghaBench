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
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int EAGAIN ; 
 int errno ; 
 int sendmsg (int,struct msghdr*,int) ; 

int uml_vector_sendmsg(int fd, void *hdr, int flags)
{
	int n;

	CATCH_EINTR(n = sendmsg(fd, (struct msghdr *) hdr,  flags));
	if ((n < 0) && (errno == EAGAIN))
		return 0;
	if (n >= 0)
		return n;
	else
		return -errno;
}