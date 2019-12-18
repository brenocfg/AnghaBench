#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct vio_device_id {int dummy; } ;
struct vio_dev {char* name; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  unit_address; } ;
struct TYPE_11__ {struct scsi_info* ldata; } ;
struct TYPE_10__ {long partition_number; } ;
struct TYPE_9__ {int /*<<< orphan*/  unit_id; int /*<<< orphan*/  partition_num; int /*<<< orphan*/  partition_name; TYPE_2__* window; } ;
struct TYPE_7__ {char* tport_name; } ;
struct scsi_info {char* eye; int /*<<< orphan*/  list; TYPE_5__ target; int /*<<< orphan*/  work_task; struct scsi_info* map_buf; scalar_t__ map_ioba; int /*<<< orphan*/  work_q; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; int /*<<< orphan*/  unconfig; int /*<<< orphan*/  wait_idle; TYPE_4__ client_data; TYPE_3__ dds; int /*<<< orphan*/  intr_lock; int /*<<< orphan*/  request_limit; TYPE_1__ tport; int /*<<< orphan*/  active_q; int /*<<< orphan*/  waiting_rsp; int /*<<< orphan*/  schedule_q; struct vio_dev* dma_dev; } ;
struct TYPE_8__ {long liobn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  H_GET_PARTNER_INFO ; 
 long H_SUCCESS ; 
 int IBMVSCSIS_NAMELEN ; 
 int /*<<< orphan*/  INITIAL_SRP_LIMIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t LOCAL ; 
 int PAGE_SIZE ; 
 size_t REMOTE ; 
 int /*<<< orphan*/  SRP_MAX_IU_LEN ; 
 int /*<<< orphan*/  WAIT_ENABLED ; 
 long be64_to_cpu (int) ; 
 int /*<<< orphan*/  create_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct scsi_info*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,struct scsi_info*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 long h_vioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ibmvscsis_alloc_cmds (struct scsi_info*,int /*<<< orphan*/ ) ; 
 int ibmvscsis_alloctimer (struct scsi_info*) ; 
 int ibmvscsis_create_command_q (struct scsi_info*,int) ; 
 int /*<<< orphan*/  ibmvscsis_destroy_command_q (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_dev_list ; 
 int /*<<< orphan*/  ibmvscsis_dev_lock ; 
 int /*<<< orphan*/  ibmvscsis_free_cmds (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_freetimer (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_handle_crq ; 
 int /*<<< orphan*/  ibmvscsis_interrupt ; 
 int /*<<< orphan*/  ibmvscsis_unregister_command_q (struct scsi_info*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct scsi_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  partition_name ; 
 int /*<<< orphan*/  partition_number ; 
 int read_dma_window (struct scsi_info*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct scsi_info*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int srp_target_alloc (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_target_free (TYPE_5__*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvscsis_probe(struct vio_dev *vdev,
			   const struct vio_device_id *id)
{
	struct scsi_info *vscsi;
	int rc = 0;
	long hrc = 0;
	char wq_name[24];

	vscsi = kzalloc(sizeof(*vscsi), GFP_KERNEL);
	if (!vscsi) {
		rc = -ENOMEM;
		dev_err(&vdev->dev, "probe: allocation of adapter failed\n");
		return rc;
	}

	vscsi->dma_dev = vdev;
	vscsi->dev = vdev->dev;
	INIT_LIST_HEAD(&vscsi->schedule_q);
	INIT_LIST_HEAD(&vscsi->waiting_rsp);
	INIT_LIST_HEAD(&vscsi->active_q);

	snprintf(vscsi->tport.tport_name, IBMVSCSIS_NAMELEN, "%s",
		 dev_name(&vdev->dev));

	dev_dbg(&vscsi->dev, "probe tport_name: %s\n", vscsi->tport.tport_name);

	rc = read_dma_window(vscsi);
	if (rc)
		goto free_adapter;
	dev_dbg(&vscsi->dev, "Probe: liobn 0x%x, riobn 0x%x\n",
		vscsi->dds.window[LOCAL].liobn,
		vscsi->dds.window[REMOTE].liobn);

	snprintf(vscsi->eye, sizeof(vscsi->eye), "VSCSI %s", vdev->name);

	vscsi->dds.unit_id = vdev->unit_address;
	strscpy(vscsi->dds.partition_name, partition_name,
		sizeof(vscsi->dds.partition_name));
	vscsi->dds.partition_num = partition_number;

	spin_lock_bh(&ibmvscsis_dev_lock);
	list_add_tail(&vscsi->list, &ibmvscsis_dev_list);
	spin_unlock_bh(&ibmvscsis_dev_lock);

	/*
	 * TBD: How do we determine # of cmds to request?  Do we know how
	 * many "children" we have?
	 */
	vscsi->request_limit = INITIAL_SRP_LIMIT;
	rc = srp_target_alloc(&vscsi->target, &vdev->dev, vscsi->request_limit,
			      SRP_MAX_IU_LEN);
	if (rc)
		goto rem_list;

	vscsi->target.ldata = vscsi;

	rc = ibmvscsis_alloc_cmds(vscsi, vscsi->request_limit);
	if (rc) {
		dev_err(&vscsi->dev, "alloc_cmds failed, rc %d, num %d\n",
			rc, vscsi->request_limit);
		goto free_target;
	}

	/*
	 * Note: the lock is used in freeing timers, so must initialize
	 * first so that ordering in case of error is correct.
	 */
	spin_lock_init(&vscsi->intr_lock);

	rc = ibmvscsis_alloctimer(vscsi);
	if (rc) {
		dev_err(&vscsi->dev, "probe: alloctimer failed, rc %d\n", rc);
		goto free_cmds;
	}

	rc = ibmvscsis_create_command_q(vscsi, 256);
	if (rc) {
		dev_err(&vscsi->dev, "probe: create_command_q failed, rc %d\n",
			rc);
		goto free_timer;
	}

	vscsi->map_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!vscsi->map_buf) {
		rc = -ENOMEM;
		dev_err(&vscsi->dev, "probe: allocating cmd buffer failed\n");
		goto destroy_queue;
	}

	vscsi->map_ioba = dma_map_single(&vdev->dev, vscsi->map_buf, PAGE_SIZE,
					 DMA_BIDIRECTIONAL);
	if (dma_mapping_error(&vdev->dev, vscsi->map_ioba)) {
		rc = -ENOMEM;
		dev_err(&vscsi->dev, "probe: error mapping command buffer\n");
		goto free_buf;
	}

	hrc = h_vioctl(vscsi->dds.unit_id, H_GET_PARTNER_INFO,
		       (u64)vscsi->map_ioba | ((u64)PAGE_SIZE << 32), 0, 0, 0,
		       0);
	if (hrc == H_SUCCESS)
		vscsi->client_data.partition_number =
			be64_to_cpu(*(u64 *)vscsi->map_buf);
	/*
	 * We expect the VIOCTL to fail if we're configured as "any
	 * client can connect" and the client isn't activated yet.
	 * We'll make the call again when he sends an init msg.
	 */
	dev_dbg(&vscsi->dev, "probe hrc %ld, client partition num %d\n",
		hrc, vscsi->client_data.partition_number);

	tasklet_init(&vscsi->work_task, ibmvscsis_handle_crq,
		     (unsigned long)vscsi);

	init_completion(&vscsi->wait_idle);
	init_completion(&vscsi->unconfig);

	snprintf(wq_name, 24, "ibmvscsis%s", dev_name(&vdev->dev));
	vscsi->work_q = create_workqueue(wq_name);
	if (!vscsi->work_q) {
		rc = -ENOMEM;
		dev_err(&vscsi->dev, "create_workqueue failed\n");
		goto unmap_buf;
	}

	rc = request_irq(vdev->irq, ibmvscsis_interrupt, 0, "ibmvscsis", vscsi);
	if (rc) {
		rc = -EPERM;
		dev_err(&vscsi->dev, "probe: request_irq failed, rc %d\n", rc);
		goto destroy_WQ;
	}

	vscsi->state = WAIT_ENABLED;

	dev_set_drvdata(&vdev->dev, vscsi);

	return 0;

destroy_WQ:
	destroy_workqueue(vscsi->work_q);
unmap_buf:
	dma_unmap_single(&vdev->dev, vscsi->map_ioba, PAGE_SIZE,
			 DMA_BIDIRECTIONAL);
free_buf:
	kfree(vscsi->map_buf);
destroy_queue:
	tasklet_kill(&vscsi->work_task);
	ibmvscsis_unregister_command_q(vscsi);
	ibmvscsis_destroy_command_q(vscsi);
free_timer:
	ibmvscsis_freetimer(vscsi);
free_cmds:
	ibmvscsis_free_cmds(vscsi);
free_target:
	srp_target_free(&vscsi->target);
rem_list:
	spin_lock_bh(&ibmvscsis_dev_lock);
	list_del(&vscsi->list);
	spin_unlock_bh(&ibmvscsis_dev_lock);
free_adapter:
	kfree(vscsi);

	return rc;
}