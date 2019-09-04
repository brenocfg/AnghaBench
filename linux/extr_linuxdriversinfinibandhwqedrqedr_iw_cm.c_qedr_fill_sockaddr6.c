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
struct TYPE_3__ {void** u6_addr32; } ;
struct TYPE_4__ {TYPE_1__ in6_u; } ;
struct sockaddr_in6 {TYPE_2__ sin6_addr; void* sin6_port; void* sin6_family; } ;
struct qed_iwarp_cm_info {int /*<<< orphan*/ * remote_ip; int /*<<< orphan*/ * local_ip; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  local_port; } ;
struct iw_cm_event {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;

/* Variables and functions */
 void* AF_INET6 ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qedr_fill_sockaddr6(const struct qed_iwarp_cm_info *cm_info,
		    struct iw_cm_event *event)
{
	struct sockaddr_in6 *laddr6 = (struct sockaddr_in6 *)&event->local_addr;
	struct sockaddr_in6 *raddr6 =
	    (struct sockaddr_in6 *)&event->remote_addr;
	int i;

	laddr6->sin6_family = AF_INET6;
	raddr6->sin6_family = AF_INET6;

	laddr6->sin6_port = htons(cm_info->local_port);
	raddr6->sin6_port = htons(cm_info->remote_port);

	for (i = 0; i < 4; i++) {
		laddr6->sin6_addr.in6_u.u6_addr32[i] =
		    htonl(cm_info->local_ip[i]);
		raddr6->sin6_addr.in6_u.u6_addr32[i] =
		    htonl(cm_info->remote_ip[i]);
	}
}