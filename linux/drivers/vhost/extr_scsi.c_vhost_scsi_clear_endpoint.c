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
typedef  size_t u8 ;
struct vhost_virtqueue {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * private_data; } ;
struct vhost_scsi_tport {int /*<<< orphan*/  tport_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  cg_item; } ;
struct se_portal_group {TYPE_1__ tpg_group; } ;
struct vhost_scsi_tpg {int /*<<< orphan*/  tv_tpg_mutex; struct se_portal_group se_tpg; int /*<<< orphan*/ * vhost_scsi; int /*<<< orphan*/  tv_tpg_vhost_count; int /*<<< orphan*/  tport_tpgt; struct vhost_scsi_tport* tport; } ;
struct vhost_scsi_target {int /*<<< orphan*/  vhost_tpgt; int /*<<< orphan*/  vhost_wwpn; } ;
struct TYPE_6__ {int nvqs; int /*<<< orphan*/  mutex; } ;
struct vhost_scsi {TYPE_3__ dev; int /*<<< orphan*/  vs_events_nr; struct vhost_scsi_tpg** vs_tpg; TYPE_2__* vqs; } ;
struct TYPE_5__ {struct vhost_virtqueue vq; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int VHOST_SCSI_MAX_TARGET ; 
 int VHOST_SCSI_MAX_VQ ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vhost_scsi_tpg**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_undepend_item (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_scsi_flush (struct vhost_scsi*) ; 
 int /*<<< orphan*/  vhost_scsi_mutex ; 
 int /*<<< orphan*/  vhost_vq_access_ok (struct vhost_virtqueue*) ; 

__attribute__((used)) static int
vhost_scsi_clear_endpoint(struct vhost_scsi *vs,
			  struct vhost_scsi_target *t)
{
	struct se_portal_group *se_tpg;
	struct vhost_scsi_tport *tv_tport;
	struct vhost_scsi_tpg *tpg;
	struct vhost_virtqueue *vq;
	bool match = false;
	int index, ret, i;
	u8 target;

	mutex_lock(&vhost_scsi_mutex);
	mutex_lock(&vs->dev.mutex);
	/* Verify that ring has been setup correctly. */
	for (index = 0; index < vs->dev.nvqs; ++index) {
		if (!vhost_vq_access_ok(&vs->vqs[index].vq)) {
			ret = -EFAULT;
			goto err_dev;
		}
	}

	if (!vs->vs_tpg) {
		ret = 0;
		goto err_dev;
	}

	for (i = 0; i < VHOST_SCSI_MAX_TARGET; i++) {
		target = i;
		tpg = vs->vs_tpg[target];
		if (!tpg)
			continue;

		mutex_lock(&tpg->tv_tpg_mutex);
		tv_tport = tpg->tport;
		if (!tv_tport) {
			ret = -ENODEV;
			goto err_tpg;
		}

		if (strcmp(tv_tport->tport_name, t->vhost_wwpn)) {
			pr_warn("tv_tport->tport_name: %s, tpg->tport_tpgt: %hu"
				" does not match t->vhost_wwpn: %s, t->vhost_tpgt: %hu\n",
				tv_tport->tport_name, tpg->tport_tpgt,
				t->vhost_wwpn, t->vhost_tpgt);
			ret = -EINVAL;
			goto err_tpg;
		}
		tpg->tv_tpg_vhost_count--;
		tpg->vhost_scsi = NULL;
		vs->vs_tpg[target] = NULL;
		match = true;
		mutex_unlock(&tpg->tv_tpg_mutex);
		/*
		 * Release se_tpg->tpg_group.cg_item configfs dependency now
		 * to allow vhost-scsi WWPN se_tpg->tpg_group shutdown to occur.
		 */
		se_tpg = &tpg->se_tpg;
		target_undepend_item(&se_tpg->tpg_group.cg_item);
	}
	if (match) {
		for (i = 0; i < VHOST_SCSI_MAX_VQ; i++) {
			vq = &vs->vqs[i].vq;
			mutex_lock(&vq->mutex);
			vq->private_data = NULL;
			mutex_unlock(&vq->mutex);
		}
	}
	/*
	 * Act as synchronize_rcu to make sure access to
	 * old vs->vs_tpg is finished.
	 */
	vhost_scsi_flush(vs);
	kfree(vs->vs_tpg);
	vs->vs_tpg = NULL;
	WARN_ON(vs->vs_events_nr);
	mutex_unlock(&vs->dev.mutex);
	mutex_unlock(&vhost_scsi_mutex);
	return 0;

err_tpg:
	mutex_unlock(&tpg->tv_tpg_mutex);
err_dev:
	mutex_unlock(&vs->dev.mutex);
	mutex_unlock(&vhost_scsi_mutex);
	return ret;
}