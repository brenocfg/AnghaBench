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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct socket* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  usnic_dbg (char*,char*) ; 
 int /*<<< orphan*/  usnic_err (char*,int,int) ; 
 int /*<<< orphan*/  usnic_transport_sock_to_str (char*,int,struct socket*) ; 

struct socket *usnic_transport_get_socket(int sock_fd)
{
	struct socket *sock;
	int err;
	char buf[25];

	/* sockfd_lookup will internally do a fget */
	sock = sockfd_lookup(sock_fd, &err);
	if (!sock) {
		usnic_err("Unable to lookup socket for fd %d with err %d\n",
				sock_fd, err);
		return ERR_PTR(-ENOENT);
	}

	usnic_transport_sock_to_str(buf, sizeof(buf), sock);
	usnic_dbg("Get sock %s\n", buf);

	return sock;
}