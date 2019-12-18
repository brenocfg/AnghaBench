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
struct se_session {struct se_node_acl* se_node_acl; } ;
struct se_node_acl {char* initiatorname; TYPE_1__* se_tpg; } ;
struct se_device {struct se_session* reservation_holder; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {char* fabric_name; } ;
struct TYPE_3__ {TYPE_2__* se_tpg_tfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t target_core_dev_pr_show_spc2_res(struct se_device *dev,
		char *page)
{
	struct se_session *sess = dev->reservation_holder;
	struct se_node_acl *se_nacl;
	ssize_t len;

	if (sess) {
		se_nacl = sess->se_node_acl;
		len = sprintf(page,
			      "SPC-2 Reservation: %s Initiator: %s\n",
			      se_nacl->se_tpg->se_tpg_tfo->fabric_name,
			      se_nacl->initiatorname);
	} else {
		len = sprintf(page, "No SPC-2 Reservation holder\n");
	}
	return len;
}