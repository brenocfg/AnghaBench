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
struct se_session {int dummy; } ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {char* initiatorname; int /*<<< orphan*/  nacl_sess_lock; struct se_portal_group* se_tpg; struct se_session* nacl_sess; } ;
struct se_lun_acl {struct se_node_acl* se_lun_nacl; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* sess_get_initiator_sid ) (struct se_session*,unsigned char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct se_lun_acl* iport_to_lacl (struct config_item*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,unsigned char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct se_session*,unsigned char*,int) ; 

__attribute__((used)) static ssize_t target_stat_iport_port_ident_show(struct config_item *item,
		char *page)
{
	struct se_lun_acl *lacl = iport_to_lacl(item);
	struct se_node_acl *nacl = lacl->se_lun_nacl;
	struct se_session *se_sess;
	struct se_portal_group *tpg;
	ssize_t ret;
	unsigned char buf[64];

	spin_lock_irq(&nacl->nacl_sess_lock);
	se_sess = nacl->nacl_sess;
	if (!se_sess) {
		spin_unlock_irq(&nacl->nacl_sess_lock);
		return -ENODEV;
	}

	tpg = nacl->se_tpg;
	/* scsiAttIntrPortName+scsiAttIntrPortIdentifier */
	memset(buf, 0, 64);
	if (tpg->se_tpg_tfo->sess_get_initiator_sid != NULL)
		tpg->se_tpg_tfo->sess_get_initiator_sid(se_sess, buf, 64);

	ret = snprintf(page, PAGE_SIZE, "%s+i+%s\n", nacl->initiatorname, buf);
	spin_unlock_irq(&nacl->nacl_sess_lock);
	return ret;
}