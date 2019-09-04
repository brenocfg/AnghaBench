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
typedef  void* u8 ;
struct mcast_port {int /*<<< orphan*/  port_num; TYPE_1__* dev; } ;
struct ib_sa_mcmember_rec {void* join_state; } ;
struct mcast_group {int /*<<< orphan*/  query; void* leave_state; struct ib_sa_mcmember_rec rec; struct mcast_port* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_SA_MCMEMBER_REC_JOIN_STATE ; 
 int IB_SA_MCMEMBER_REC_MGID ; 
 int IB_SA_MCMEMBER_REC_PORT_GID ; 
 int /*<<< orphan*/  IB_SA_METHOD_DELETE ; 
 int ib_sa_mcmember_rec_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_sa_mcmember_rec*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mcast_group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leave_handler ; 
 int /*<<< orphan*/  sa_client ; 

__attribute__((used)) static int send_leave(struct mcast_group *group, u8 leave_state)
{
	struct mcast_port *port = group->port;
	struct ib_sa_mcmember_rec rec;
	int ret;

	rec = group->rec;
	rec.join_state = leave_state;
	group->leave_state = leave_state;

	ret = ib_sa_mcmember_rec_query(&sa_client, port->dev->device,
				       port->port_num, IB_SA_METHOD_DELETE, &rec,
				       IB_SA_MCMEMBER_REC_MGID     |
				       IB_SA_MCMEMBER_REC_PORT_GID |
				       IB_SA_MCMEMBER_REC_JOIN_STATE,
				       3000, GFP_KERNEL, leave_handler,
				       group, &group->query);
	return (ret > 0) ? 0 : ret;
}