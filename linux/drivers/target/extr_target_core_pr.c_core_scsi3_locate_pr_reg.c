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
struct t10_pr_registration {int dummy; } ;
struct se_session {int dummy; } ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {struct se_portal_group* se_tpg; } ;
struct se_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sess_get_initiator_sid ) (struct se_session*,unsigned char*,int) ;} ;

/* Variables and functions */
 int PR_REG_ISID_LEN ; 
 struct t10_pr_registration* __core_scsi3_locate_pr_reg (struct se_device*,struct se_node_acl*,unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct se_session*,unsigned char*,int) ; 

__attribute__((used)) static struct t10_pr_registration *core_scsi3_locate_pr_reg(
	struct se_device *dev,
	struct se_node_acl *nacl,
	struct se_session *sess)
{
	struct se_portal_group *tpg = nacl->se_tpg;
	unsigned char buf[PR_REG_ISID_LEN], *isid_ptr = NULL;

	if (tpg->se_tpg_tfo->sess_get_initiator_sid != NULL) {
		memset(&buf[0], 0, PR_REG_ISID_LEN);
		tpg->se_tpg_tfo->sess_get_initiator_sid(sess, &buf[0],
					PR_REG_ISID_LEN);
		isid_ptr = &buf[0];
	}

	return __core_scsi3_locate_pr_reg(dev, nacl, isid_ptr);
}