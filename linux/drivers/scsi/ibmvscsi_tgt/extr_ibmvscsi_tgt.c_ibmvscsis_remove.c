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
struct vio_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct scsi_info {int /*<<< orphan*/  list; int /*<<< orphan*/  target; int /*<<< orphan*/  work_task; struct scsi_info* map_buf; int /*<<< orphan*/  map_ioba; int /*<<< orphan*/  work_q; int /*<<< orphan*/  unconfig; int /*<<< orphan*/  intr_lock; int /*<<< orphan*/  flags; TYPE_1__* dma_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_SLEEPING ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  UNCONFIGURING ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct scsi_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_destroy_command_q (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_dev_lock ; 
 int /*<<< orphan*/  ibmvscsis_free_cmds (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_freetimer (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scsi_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_target_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vio_disable_interrupts (struct vio_dev*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvscsis_remove(struct vio_dev *vdev)
{
	struct scsi_info *vscsi = dev_get_drvdata(&vdev->dev);

	dev_dbg(&vscsi->dev, "remove (%s)\n", dev_name(&vscsi->dma_dev->dev));

	spin_lock_bh(&vscsi->intr_lock);
	ibmvscsis_post_disconnect(vscsi, UNCONFIGURING, 0);
	vscsi->flags |= CFG_SLEEPING;
	spin_unlock_bh(&vscsi->intr_lock);
	wait_for_completion(&vscsi->unconfig);

	vio_disable_interrupts(vdev);
	free_irq(vdev->irq, vscsi);
	destroy_workqueue(vscsi->work_q);
	dma_unmap_single(&vdev->dev, vscsi->map_ioba, PAGE_SIZE,
			 DMA_BIDIRECTIONAL);
	kfree(vscsi->map_buf);
	tasklet_kill(&vscsi->work_task);
	ibmvscsis_destroy_command_q(vscsi);
	ibmvscsis_freetimer(vscsi);
	ibmvscsis_free_cmds(vscsi);
	srp_target_free(&vscsi->target);
	spin_lock_bh(&ibmvscsis_dev_lock);
	list_del(&vscsi->list);
	spin_unlock_bh(&ibmvscsis_dev_lock);
	kfree(vscsi);

	return 0;
}