#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cg_item; } ;
struct t10_alua_tg_pt_gp {int /*<<< orphan*/  tg_pt_gp_id; TYPE_6__ tg_pt_gp_group; } ;
struct se_portal_group {TYPE_4__* se_tpg_tfo; } ;
struct TYPE_11__ {int /*<<< orphan*/  cg_item; } ;
struct se_lun {TYPE_5__ lun_group; int /*<<< orphan*/  lun_tg_pt_gp_lock; struct t10_alua_tg_pt_gp* lun_tg_pt_gp; int /*<<< orphan*/  lun_se_dev; struct se_portal_group* lun_tpg; } ;
struct TYPE_9__ {struct t10_alua_tg_pt_gp* default_tg_pt_gp; } ;
struct se_device {TYPE_3__ t10_alua; TYPE_2__* se_hba; TYPE_1__* transport; } ;
typedef  size_t ssize_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/  (* tpg_get_wwn ) (struct se_portal_group*) ;} ;
struct TYPE_8__ {int hba_flags; } ;
struct TYPE_7__ {int transport_flags; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int HBA_FLAGS_INTERNAL_USE ; 
 int TG_PT_GROUP_NAME_BUF ; 
 int TRANSPORT_FLAG_PASSTHROUGH_ALUA ; 
 int /*<<< orphan*/  __target_attach_tg_pt_gp (struct se_lun*,struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  __target_detach_tg_pt_gp (struct se_lun*,struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 struct t10_alua_tg_pt_gp* core_alua_get_tg_pt_gp_by_name (struct se_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_alua_put_tg_pt_gp_from_name (struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct se_device* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strstrip (unsigned char*) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub2 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub3 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub4 (struct se_portal_group*) ; 

ssize_t core_alua_store_tg_pt_gp_info(
	struct se_lun *lun,
	const char *page,
	size_t count)
{
	struct se_portal_group *tpg = lun->lun_tpg;
	/*
	 * rcu_dereference_raw protected by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	struct se_device *dev = rcu_dereference_raw(lun->lun_se_dev);
	struct t10_alua_tg_pt_gp *tg_pt_gp = NULL, *tg_pt_gp_new = NULL;
	unsigned char buf[TG_PT_GROUP_NAME_BUF];
	int move = 0;

	if (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA ||
	    (dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		return -ENODEV;

	if (count > TG_PT_GROUP_NAME_BUF) {
		pr_err("ALUA Target Port Group alias too large!\n");
		return -EINVAL;
	}
	memset(buf, 0, TG_PT_GROUP_NAME_BUF);
	memcpy(buf, page, count);
	/*
	 * Any ALUA target port group alias besides "NULL" means we will be
	 * making a new group association.
	 */
	if (strcmp(strstrip(buf), "NULL")) {
		/*
		 * core_alua_get_tg_pt_gp_by_name() will increment reference to
		 * struct t10_alua_tg_pt_gp.  This reference is released with
		 * core_alua_put_tg_pt_gp_from_name() below.
		 */
		tg_pt_gp_new = core_alua_get_tg_pt_gp_by_name(dev,
					strstrip(buf));
		if (!tg_pt_gp_new)
			return -ENODEV;
	}

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	if (tg_pt_gp) {
		/*
		 * Clearing an existing tg_pt_gp association, and replacing
		 * with the default_tg_pt_gp.
		 */
		if (!tg_pt_gp_new) {
			pr_debug("Target_Core_ConfigFS: Moving"
				" %s/tpgt_%hu/%s from ALUA Target Port Group:"
				" alua/%s, ID: %hu back to"
				" default_tg_pt_gp\n",
				tpg->se_tpg_tfo->tpg_get_wwn(tpg),
				tpg->se_tpg_tfo->tpg_get_tag(tpg),
				config_item_name(&lun->lun_group.cg_item),
				config_item_name(
					&tg_pt_gp->tg_pt_gp_group.cg_item),
				tg_pt_gp->tg_pt_gp_id);

			__target_detach_tg_pt_gp(lun, tg_pt_gp);
			__target_attach_tg_pt_gp(lun,
					dev->t10_alua.default_tg_pt_gp);
			spin_unlock(&lun->lun_tg_pt_gp_lock);

			return count;
		}
		__target_detach_tg_pt_gp(lun, tg_pt_gp);
		move = 1;
	}

	__target_attach_tg_pt_gp(lun, tg_pt_gp_new);
	spin_unlock(&lun->lun_tg_pt_gp_lock);
	pr_debug("Target_Core_ConfigFS: %s %s/tpgt_%hu/%s to ALUA"
		" Target Port Group: alua/%s, ID: %hu\n", (move) ?
		"Moving" : "Adding", tpg->se_tpg_tfo->tpg_get_wwn(tpg),
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		config_item_name(&lun->lun_group.cg_item),
		config_item_name(&tg_pt_gp_new->tg_pt_gp_group.cg_item),
		tg_pt_gp_new->tg_pt_gp_id);

	core_alua_put_tg_pt_gp_from_name(tg_pt_gp_new);
	return count;
}