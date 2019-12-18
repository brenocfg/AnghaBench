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
struct TYPE_3__ {int /*<<< orphan*/  ss_family; } ;
struct iscsi_np {TYPE_1__ np_sockaddr; } ;
struct iscsi_conn {int /*<<< orphan*/  local_sockaddr; int /*<<< orphan*/  login_sockaddr; int /*<<< orphan*/  login_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  local_addr; int /*<<< orphan*/  remote_addr; } ;
struct cxgbit_sock {TYPE_2__ com; } ;

/* Variables and functions */

__attribute__((used)) static void
cxgbit_set_conn_info(struct iscsi_np *np, struct iscsi_conn *conn,
		     struct cxgbit_sock *csk)
{
	conn->login_family = np->np_sockaddr.ss_family;
	conn->login_sockaddr = csk->com.remote_addr;
	conn->local_sockaddr = csk->com.local_addr;
}