#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; void* sin_port; void* sin_family; } ;
struct iw_cm_event {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct i40iw_cm_node {int /*<<< orphan*/ * rem_addr; int /*<<< orphan*/ * loc_addr; int /*<<< orphan*/  rem_port; int /*<<< orphan*/  loc_port; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i40iw_fill_sockaddr4(struct i40iw_cm_node *cm_node,
					struct iw_cm_event *event)
{
	struct sockaddr_in *laddr = (struct sockaddr_in *)&event->local_addr;
	struct sockaddr_in *raddr = (struct sockaddr_in *)&event->remote_addr;

	laddr->sin_family = AF_INET;
	raddr->sin_family = AF_INET;

	laddr->sin_port = htons(cm_node->loc_port);
	raddr->sin_port = htons(cm_node->rem_port);

	laddr->sin_addr.s_addr = htonl(cm_node->loc_addr[0]);
	raddr->sin_addr.s_addr = htonl(cm_node->rem_addr[0]);
}