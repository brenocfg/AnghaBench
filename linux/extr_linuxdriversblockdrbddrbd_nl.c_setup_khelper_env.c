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
struct sockaddr_in6 {char sin6_addr; } ;
struct sockaddr_in {char sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct drbd_connection {scalar_t__ my_addr_len; scalar_t__ peer_addr_len; int /*<<< orphan*/  peer_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void setup_khelper_env(struct drbd_connection *connection, char **envp)
{
	char *afs;

	/* FIXME: A future version will not allow this case. */
	if (connection->my_addr_len == 0 || connection->peer_addr_len == 0)
		return;

	switch (((struct sockaddr *)&connection->peer_addr)->sa_family) {
	case AF_INET6:
		afs = "ipv6";
		snprintf(envp[4], 60, "DRBD_PEER_ADDRESS=%pI6",
			 &((struct sockaddr_in6 *)&connection->peer_addr)->sin6_addr);
		break;
	case AF_INET:
		afs = "ipv4";
		snprintf(envp[4], 60, "DRBD_PEER_ADDRESS=%pI4",
			 &((struct sockaddr_in *)&connection->peer_addr)->sin_addr);
		break;
	default:
		afs = "ssocks";
		snprintf(envp[4], 60, "DRBD_PEER_ADDRESS=%pI4",
			 &((struct sockaddr_in *)&connection->peer_addr)->sin_addr);
	}
	snprintf(envp[3], 20, "DRBD_PEER_AF=%s", afs);
}