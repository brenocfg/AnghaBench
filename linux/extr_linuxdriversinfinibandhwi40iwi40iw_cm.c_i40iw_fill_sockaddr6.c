#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_4__ {TYPE_1__ in6_u; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; void* sin6_port; void* sin6_family; } ;
struct iw_cm_event {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct i40iw_cm_node {int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  rem_port; int /*<<< orphan*/  loc_port; } ;

/* Variables and functions */
 void* AF_INET6 ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_copy_ip_htonl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i40iw_fill_sockaddr6(struct i40iw_cm_node *cm_node,
					struct iw_cm_event *event)
{
	struct sockaddr_in6 *laddr6 = (struct sockaddr_in6 *)&event->local_addr;
	struct sockaddr_in6 *raddr6 = (struct sockaddr_in6 *)&event->remote_addr;

	laddr6->sin6_family = AF_INET6;
	raddr6->sin6_family = AF_INET6;

	laddr6->sin6_port = htons(cm_node->loc_port);
	raddr6->sin6_port = htons(cm_node->rem_port);

	i40iw_copy_ip_htonl(laddr6->sin6_addr.in6_u.u6_addr32,
			    cm_node->loc_addr);
	i40iw_copy_ip_htonl(raddr6->sin6_addr.in6_u.u6_addr32,
			    cm_node->rem_addr);
}