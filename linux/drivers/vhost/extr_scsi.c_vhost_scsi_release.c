#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vhost_scsi_target {int /*<<< orphan*/  vhost_wwpn; } ;
struct TYPE_3__ {int /*<<< orphan*/  vqs; int /*<<< orphan*/  mutex; } ;
struct vhost_scsi {TYPE_1__ dev; int /*<<< orphan*/  vs_vhost_wwpn; } ;
struct inode {int dummy; } ;
struct file {struct vhost_scsi* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct vhost_scsi*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_dev_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  vhost_dev_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  vhost_scsi_clear_endpoint (struct vhost_scsi*,struct vhost_scsi_target*) ; 
 int /*<<< orphan*/  vhost_scsi_flush (struct vhost_scsi*) ; 

__attribute__((used)) static int vhost_scsi_release(struct inode *inode, struct file *f)
{
	struct vhost_scsi *vs = f->private_data;
	struct vhost_scsi_target t;

	mutex_lock(&vs->dev.mutex);
	memcpy(t.vhost_wwpn, vs->vs_vhost_wwpn, sizeof(t.vhost_wwpn));
	mutex_unlock(&vs->dev.mutex);
	vhost_scsi_clear_endpoint(vs, &t);
	vhost_dev_stop(&vs->dev);
	vhost_dev_cleanup(&vs->dev);
	/* Jobs can re-queue themselves in evt kick handler. Do extra flush. */
	vhost_scsi_flush(vs);
	kfree(vs->dev.vqs);
	kvfree(vs);
	return 0;
}