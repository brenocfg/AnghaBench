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
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {int /*<<< orphan*/  initiatorname; } ;
struct se_lun_acl {int /*<<< orphan*/  mapped_lun; struct se_lun* se_lun; struct se_node_acl* se_lun_nacl; } ;
struct se_lun {int /*<<< orphan*/  unpacked_lun; scalar_t__ lun_access_ro; int /*<<< orphan*/  lun_se_dev; } ;
struct se_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ core_enable_device_list_for_node (struct se_lun*,struct se_lun_acl*,int /*<<< orphan*/ ,int,struct se_node_acl*,struct se_portal_group*) ; 
 int /*<<< orphan*/  core_scsi3_check_aptpl_registration (struct se_device*,struct se_portal_group*,struct se_lun*,struct se_node_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct se_device* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 

int core_dev_add_initiator_node_lun_acl(
	struct se_portal_group *tpg,
	struct se_lun_acl *lacl,
	struct se_lun *lun,
	bool lun_access_ro)
{
	struct se_node_acl *nacl = lacl->se_lun_nacl;
	/*
	 * rcu_dereference_raw protected by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	struct se_device *dev = rcu_dereference_raw(lun->lun_se_dev);

	if (!nacl)
		return -EINVAL;

	if (lun->lun_access_ro)
		lun_access_ro = true;

	lacl->se_lun = lun;

	if (core_enable_device_list_for_node(lun, lacl, lacl->mapped_lun,
			lun_access_ro, nacl, tpg) < 0)
		return -EINVAL;

	pr_debug("%s_TPG[%hu]_LUN[%llu->%llu] - Added %s ACL for "
		" InitiatorNode: %s\n", tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), lun->unpacked_lun, lacl->mapped_lun,
		lun_access_ro ? "RO" : "RW",
		nacl->initiatorname);
	/*
	 * Check to see if there are any existing persistent reservation APTPL
	 * pre-registrations that need to be enabled for this LUN ACL..
	 */
	core_scsi3_check_aptpl_registration(dev, tpg, lun, nacl,
					    lacl->mapped_lun);
	return 0;
}