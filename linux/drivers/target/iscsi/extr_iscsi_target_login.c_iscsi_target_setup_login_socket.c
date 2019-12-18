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
struct sockaddr_storage {int dummy; } ;
struct iscsit_transport {int (* iscsit_setup_np ) (struct iscsi_np*,struct sockaddr_storage*) ;} ;
struct iscsi_np {int enabled; struct iscsit_transport* np_transport; int /*<<< orphan*/  np_network_transport; } ;

/* Variables and functions */
 int EINVAL ; 
 struct iscsit_transport* iscsit_get_transport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_put_transport (struct iscsit_transport*) ; 
 int stub1 (struct iscsi_np*,struct sockaddr_storage*) ; 

int iscsi_target_setup_login_socket(
	struct iscsi_np *np,
	struct sockaddr_storage *sockaddr)
{
	struct iscsit_transport *t;
	int rc;

	t = iscsit_get_transport(np->np_network_transport);
	if (!t)
		return -EINVAL;

	rc = t->iscsit_setup_np(np, sockaddr);
	if (rc < 0) {
		iscsit_put_transport(t);
		return rc;
	}

	np->np_transport = t;
	np->enabled = true;
	return 0;
}