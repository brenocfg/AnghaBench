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
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 int /*<<< orphan*/  usnic_dbg (char*,char*) ; 
 int /*<<< orphan*/  usnic_transport_sock_to_str (char*,int,struct socket*) ; 

void usnic_transport_put_socket(struct socket *sock)
{
	char buf[100];

	usnic_transport_sock_to_str(buf, sizeof(buf), sock);
	usnic_dbg("Put sock %s\n", buf);
	sockfd_put(sock);
}