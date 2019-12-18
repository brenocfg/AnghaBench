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
struct scsi_device {int dummy; } ;
struct alua_port_group {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; int /*<<< orphan*/  dh_list; int /*<<< orphan*/  device_id_str; scalar_t__ device_id_len; } ;
struct alua_dh_data {int /*<<< orphan*/  pg_lock; int /*<<< orphan*/  pg; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_DH_NAME ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ IS_ERR (struct alua_port_group*) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PTR_ERR (struct alua_port_group*) ; 
 int SCSI_DH_DEV_UNSUPP ; 
 int SCSI_DH_NOMEM ; 
 int SCSI_DH_OK ; 
 struct alua_port_group* alua_alloc_pg (struct scsi_device*,int,int) ; 
 int /*<<< orphan*/  alua_rtpg_queue (struct alua_port_group*,struct scsi_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct alua_port_group*) ; 
 struct alua_port_group* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_port_group ; 
 int scsi_vpd_tpg_id (struct scsi_device*,int*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int alua_check_vpd(struct scsi_device *sdev, struct alua_dh_data *h,
			  int tpgs)
{
	int rel_port = -1, group_id;
	struct alua_port_group *pg, *old_pg = NULL;
	bool pg_updated = false;
	unsigned long flags;

	group_id = scsi_vpd_tpg_id(sdev, &rel_port);
	if (group_id < 0) {
		/*
		 * Internal error; TPGS supported but required
		 * VPD identification descriptors not present.
		 * Disable ALUA support
		 */
		sdev_printk(KERN_INFO, sdev,
			    "%s: No target port descriptors found\n",
			    ALUA_DH_NAME);
		return SCSI_DH_DEV_UNSUPP;
	}

	pg = alua_alloc_pg(sdev, group_id, tpgs);
	if (IS_ERR(pg)) {
		if (PTR_ERR(pg) == -ENOMEM)
			return SCSI_DH_NOMEM;
		return SCSI_DH_DEV_UNSUPP;
	}
	if (pg->device_id_len)
		sdev_printk(KERN_INFO, sdev,
			    "%s: device %s port group %x rel port %x\n",
			    ALUA_DH_NAME, pg->device_id_str,
			    group_id, rel_port);
	else
		sdev_printk(KERN_INFO, sdev,
			    "%s: port group %x rel port %x\n",
			    ALUA_DH_NAME, group_id, rel_port);

	/* Check for existing port group references */
	spin_lock(&h->pg_lock);
	old_pg = rcu_dereference_protected(h->pg, lockdep_is_held(&h->pg_lock));
	if (old_pg != pg) {
		/* port group has changed. Update to new port group */
		if (h->pg) {
			spin_lock_irqsave(&old_pg->lock, flags);
			list_del_rcu(&h->node);
			spin_unlock_irqrestore(&old_pg->lock, flags);
		}
		rcu_assign_pointer(h->pg, pg);
		pg_updated = true;
	}

	spin_lock_irqsave(&pg->lock, flags);
	if (pg_updated)
		list_add_rcu(&h->node, &pg->dh_list);
	spin_unlock_irqrestore(&pg->lock, flags);

	alua_rtpg_queue(rcu_dereference_protected(h->pg,
						  lockdep_is_held(&h->pg_lock)),
			sdev, NULL, true);
	spin_unlock(&h->pg_lock);

	if (old_pg)
		kref_put(&old_pg->kref, release_port_group);

	return SCSI_DH_OK;
}