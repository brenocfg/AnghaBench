#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct se_portal_group {int /*<<< orphan*/  tpg_lun_mutex; int /*<<< orphan*/  tpg_lun_hlist; } ;
struct se_lun {int lun_access_ro; int /*<<< orphan*/  lun_ref; int /*<<< orphan*/  link; int /*<<< orphan*/  lun_dev_link; int /*<<< orphan*/  lun_se_dev; int /*<<< orphan*/  lun_index; } ;
struct TYPE_5__ {int /*<<< orphan*/  default_tg_pt_gp; } ;
struct se_device {int dev_flags; TYPE_3__* se_hba; int /*<<< orphan*/  se_port_lock; int /*<<< orphan*/  dev_sep_list; int /*<<< orphan*/  export_count; int /*<<< orphan*/  dev_index; TYPE_2__ t10_alua; TYPE_1__* transport; } ;
struct TYPE_6__ {int hba_flags; } ;
struct TYPE_4__ {int transport_flags; } ;

/* Variables and functions */
 int DF_READ_ONLY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HBA_FLAGS_INTERNAL_USE ; 
 int TRANSPORT_FLAG_PASSTHROUGH_ALUA ; 
 int core_alloc_rtpi (struct se_lun*,struct se_device*) ; 
 int /*<<< orphan*/  core_tpg_lun_ref_release ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int percpu_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct se_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_attach_tg_pt_gp (struct se_lun*,int /*<<< orphan*/ ) ; 

int core_tpg_add_lun(
	struct se_portal_group *tpg,
	struct se_lun *lun,
	bool lun_access_ro,
	struct se_device *dev)
{
	int ret;

	ret = percpu_ref_init(&lun->lun_ref, core_tpg_lun_ref_release, 0,
			      GFP_KERNEL);
	if (ret < 0)
		goto out;

	ret = core_alloc_rtpi(lun, dev);
	if (ret)
		goto out_kill_ref;

	if (!(dev->transport->transport_flags &
	     TRANSPORT_FLAG_PASSTHROUGH_ALUA) &&
	    !(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		target_attach_tg_pt_gp(lun, dev->t10_alua.default_tg_pt_gp);

	mutex_lock(&tpg->tpg_lun_mutex);

	spin_lock(&dev->se_port_lock);
	lun->lun_index = dev->dev_index;
	rcu_assign_pointer(lun->lun_se_dev, dev);
	dev->export_count++;
	list_add_tail(&lun->lun_dev_link, &dev->dev_sep_list);
	spin_unlock(&dev->se_port_lock);

	if (dev->dev_flags & DF_READ_ONLY)
		lun->lun_access_ro = true;
	else
		lun->lun_access_ro = lun_access_ro;
	if (!(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		hlist_add_head_rcu(&lun->link, &tpg->tpg_lun_hlist);
	mutex_unlock(&tpg->tpg_lun_mutex);

	return 0;

out_kill_ref:
	percpu_ref_exit(&lun->lun_ref);
out:
	return ret;
}