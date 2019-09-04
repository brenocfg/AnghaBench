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
struct socket {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MSG_DONTWAIT ; 
 int MSG_PEEK ; 
 int drbd_recv_short (struct socket*,char*,int,int) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static bool drbd_socket_okay(struct socket **sock)
{
	int rr;
	char tb[4];

	if (!*sock)
		return false;

	rr = drbd_recv_short(*sock, tb, 4, MSG_DONTWAIT | MSG_PEEK);

	if (rr > 0 || rr == -EAGAIN) {
		return true;
	} else {
		sock_release(*sock);
		*sock = NULL;
		return false;
	}
}