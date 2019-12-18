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
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwpm_print_sockaddr(struct sockaddr_storage *sockaddr, char *msg)
{
	struct sockaddr_in6 *sockaddr_v6;
	struct sockaddr_in *sockaddr_v4;

	switch (sockaddr->ss_family) {
	case AF_INET:
		sockaddr_v4 = (struct sockaddr_in *)sockaddr;
		pr_debug("%s IPV4 %pI4: %u(0x%04X)\n",
			msg, &sockaddr_v4->sin_addr,
			ntohs(sockaddr_v4->sin_port),
			ntohs(sockaddr_v4->sin_port));
		break;
	case AF_INET6:
		sockaddr_v6 = (struct sockaddr_in6 *)sockaddr;
		pr_debug("%s IPV6 %pI6: %u(0x%04X)\n",
			msg, &sockaddr_v6->sin6_addr,
			ntohs(sockaddr_v6->sin6_port),
			ntohs(sockaddr_v6->sin6_port));
		break;
	default:
		break;
	}
}