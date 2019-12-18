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
struct TYPE_4__ {int /*<<< orphan*/  src_addr; int /*<<< orphan*/  dst_addr; } ;
struct rdma_route {TYPE_2__ addr; } ;
struct rdma_cm_id {struct rdma_route route; } ;
struct isert_conn {struct rdma_cm_id* cm_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  ss_family; } ;
struct iscsi_np {TYPE_1__ np_sockaddr; } ;
struct iscsi_conn {int /*<<< orphan*/  local_sockaddr; int /*<<< orphan*/  login_sockaddr; int /*<<< orphan*/  login_family; } ;

/* Variables and functions */

__attribute__((used)) static void
isert_set_conn_info(struct iscsi_np *np, struct iscsi_conn *conn,
		    struct isert_conn *isert_conn)
{
	struct rdma_cm_id *cm_id = isert_conn->cm_id;
	struct rdma_route *cm_route = &cm_id->route;

	conn->login_family = np->np_sockaddr.ss_family;

	conn->login_sockaddr = cm_route->addr.dst_addr;
	conn->local_sockaddr = cm_route->addr.src_addr;
}