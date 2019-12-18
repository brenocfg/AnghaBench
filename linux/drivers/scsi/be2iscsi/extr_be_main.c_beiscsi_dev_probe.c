#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wq_name ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int device; int /*<<< orphan*/  dev; } ;
struct hwi_controller {struct hwi_context_memory* phwi_ctxt; } ;
struct hwi_context_memory {struct be_eq_obj* be_eq; } ;
struct TYPE_11__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  va; int /*<<< orphan*/  size; } ;
struct TYPE_15__ {int* mcc_tag; TYPE_2__ mbox_mem_alloced; scalar_t__ mcc_free_index; scalar_t__ mcc_alloc_index; TYPE_1__* ptag_state; int /*<<< orphan*/  mcc_tag_available; scalar_t__* mcc_tag_status; int /*<<< orphan*/ * mcc_wait; } ;
struct TYPE_12__ {int /*<<< orphan*/  ios_per_ctrl; int /*<<< orphan*/  cxns_per_ctrl; } ;
struct beiscsi_hba {int mac_addr_set; int num_cpus; TYPE_6__* shost; TYPE_4__* pcidev; TYPE_8__ ctrl; int /*<<< orphan*/  wq; int /*<<< orphan*/  hw_check; int /*<<< orphan*/  recover_port; int /*<<< orphan*/  sess_work; int /*<<< orphan*/  eqd_update; int /*<<< orphan*/  state; int /*<<< orphan*/  boot_work; struct hwi_controller* phwi_ctrlr; TYPE_3__ params; int /*<<< orphan*/  async_pdu_lock; int /*<<< orphan*/  mgmt_sgl_lock; int /*<<< orphan*/  io_sgl_lock; int /*<<< orphan*/  generation; void* iotask_fn; } ;
struct be_eq_obj {int /*<<< orphan*/  iopoll; int /*<<< orphan*/  mcc_work; } ;
struct be_dma_mem {int dummy; } ;
struct TYPE_14__ {int host_no; int /*<<< orphan*/  can_queue; int /*<<< orphan*/  max_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; scalar_t__ msix_enabled; } ;
struct TYPE_10__ {int /*<<< orphan*/  tag_mem_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_EQD_UPDATE_INTERVAL ; 
 int /*<<< orphan*/  BEISCSI_HBA_BOOT_FOUND ; 
 int /*<<< orphan*/  BEISCSI_HBA_ONLINE ; 
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  BEISCSI_UE_DETECT_INTERVAL ; 
#define  BE_DEVICE_ID1 133 
#define  BE_DEVICE_ID2 132 
 int /*<<< orphan*/  BE_GEN2 ; 
 int /*<<< orphan*/  BE_GEN3 ; 
 int /*<<< orphan*/  BE_GEN4 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int MAX_MCC_CMD ; 
#define  OC_DEVICE_ID1 131 
#define  OC_DEVICE_ID2 130 
#define  OC_DEVICE_ID3 129 
#define  OC_SKH_ID1 128 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  be2iscsi_enable_msix (struct beiscsi_hba*) ; 
 int be_ctrl_init (struct beiscsi_hba*,struct pci_dev*) ; 
 int /*<<< orphan*/  be_iopoll ; 
 int /*<<< orphan*/  be_iopoll_budget ; 
 int beiscsi_boot_get_shandle (struct beiscsi_hba*,unsigned int*) ; 
 int /*<<< orphan*/  beiscsi_boot_work ; 
 int /*<<< orphan*/  beiscsi_cleanup_port (struct beiscsi_hba*) ; 
 int beiscsi_enable_pci (struct pci_dev*) ; 
 int /*<<< orphan*/  beiscsi_eqd_update_work ; 
 int /*<<< orphan*/  beiscsi_free_irqs (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_free_mem (struct beiscsi_hba*) ; 
 int beiscsi_get_fw_config (TYPE_8__*,struct beiscsi_hba*) ; 
 int beiscsi_get_memory (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_get_params (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_get_port_name (TYPE_8__*,struct beiscsi_hba*) ; 
 struct beiscsi_hba* beiscsi_hba_alloc (struct pci_dev*) ; 
 int /*<<< orphan*/  beiscsi_hba_attrs_init (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_hw_health_check ; 
 int /*<<< orphan*/  beiscsi_iface_create_default (struct beiscsi_hba*) ; 
 int beiscsi_init_irqs (struct beiscsi_hba*) ; 
 int beiscsi_init_port (struct beiscsi_hba*) ; 
 int beiscsi_init_sliport (struct beiscsi_hba*) ; 
 void* beiscsi_iotask ; 
 void* beiscsi_iotask_v2 ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  beiscsi_mcc_work ; 
 int /*<<< orphan*/  beiscsi_recover_port ; 
 int /*<<< orphan*/  beiscsi_sess_work ; 
 int /*<<< orphan*/  beiscsi_set_host_data (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_set_uer_feature (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_start_boot_work (struct beiscsi_hba*,unsigned int) ; 
 int /*<<< orphan*/  beiscsi_unmap_pci_function (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwi_cleanup_port (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  hwi_disable_intr (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  hwi_enable_intr (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_poll_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iscsi_host_add (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_host_free (TYPE_6__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_4__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_4__*) ; 
 int pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beiscsi_dev_probe(struct pci_dev *pcidev,
			     const struct pci_device_id *id)
{
	struct hwi_context_memory *phwi_context;
	struct hwi_controller *phwi_ctrlr;
	struct beiscsi_hba *phba = NULL;
	struct be_eq_obj *pbe_eq;
	unsigned int s_handle;
	char wq_name[20];
	int ret, i;

	ret = beiscsi_enable_pci(pcidev);
	if (ret < 0) {
		dev_err(&pcidev->dev,
			"beiscsi_dev_probe - Failed to enable pci device\n");
		return ret;
	}

	phba = beiscsi_hba_alloc(pcidev);
	if (!phba) {
		dev_err(&pcidev->dev,
			"beiscsi_dev_probe - Failed in beiscsi_hba_alloc\n");
		ret = -ENOMEM;
		goto disable_pci;
	}

	/* Enable EEH reporting */
	ret = pci_enable_pcie_error_reporting(pcidev);
	if (ret)
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_INIT,
			    "BM_%d : PCIe Error Reporting "
			    "Enabling Failed\n");

	pci_save_state(pcidev);

	/* Initialize Driver configuration Paramters */
	beiscsi_hba_attrs_init(phba);

	phba->mac_addr_set = false;

	switch (pcidev->device) {
	case BE_DEVICE_ID1:
	case OC_DEVICE_ID1:
	case OC_DEVICE_ID2:
		phba->generation = BE_GEN2;
		phba->iotask_fn = beiscsi_iotask;
		dev_warn(&pcidev->dev,
			 "Obsolete/Unsupported BE2 Adapter Family\n");
		break;
	case BE_DEVICE_ID2:
	case OC_DEVICE_ID3:
		phba->generation = BE_GEN3;
		phba->iotask_fn = beiscsi_iotask;
		break;
	case OC_SKH_ID1:
		phba->generation = BE_GEN4;
		phba->iotask_fn = beiscsi_iotask_v2;
		break;
	default:
		phba->generation = 0;
	}

	ret = be_ctrl_init(phba, pcidev);
	if (ret) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : be_ctrl_init failed\n");
		goto free_hba;
	}

	ret = beiscsi_init_sliport(phba);
	if (ret)
		goto free_hba;

	spin_lock_init(&phba->io_sgl_lock);
	spin_lock_init(&phba->mgmt_sgl_lock);
	spin_lock_init(&phba->async_pdu_lock);
	ret = beiscsi_get_fw_config(&phba->ctrl, phba);
	if (ret != 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : Error getting fw config\n");
		goto free_port;
	}
	beiscsi_get_port_name(&phba->ctrl, phba);
	beiscsi_get_params(phba);
	beiscsi_set_host_data(phba);
	beiscsi_set_uer_feature(phba);

	be2iscsi_enable_msix(phba);

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "BM_%d : num_cpus = %d\n",
		    phba->num_cpus);

	phba->shost->max_id = phba->params.cxns_per_ctrl;
	phba->shost->can_queue = phba->params.ios_per_ctrl;
	ret = beiscsi_get_memory(phba);
	if (ret < 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : alloc host mem failed\n");
		goto free_port;
	}

	ret = beiscsi_init_port(phba);
	if (ret < 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : init port failed\n");
		beiscsi_free_mem(phba);
		goto free_port;
	}

	for (i = 0; i < MAX_MCC_CMD; i++) {
		init_waitqueue_head(&phba->ctrl.mcc_wait[i + 1]);
		phba->ctrl.mcc_tag[i] = i + 1;
		phba->ctrl.mcc_tag_status[i + 1] = 0;
		phba->ctrl.mcc_tag_available++;
		memset(&phba->ctrl.ptag_state[i].tag_mem_state, 0,
		       sizeof(struct be_dma_mem));
	}

	phba->ctrl.mcc_alloc_index = phba->ctrl.mcc_free_index = 0;

	snprintf(wq_name, sizeof(wq_name), "beiscsi_%02x_wq",
		 phba->shost->host_no);
	phba->wq = alloc_workqueue("%s", WQ_MEM_RECLAIM, 1, wq_name);
	if (!phba->wq) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : beiscsi_dev_probe-"
			    "Failed to allocate work queue\n");
		ret = -ENOMEM;
		goto free_twq;
	}

	INIT_DELAYED_WORK(&phba->eqd_update, beiscsi_eqd_update_work);

	phwi_ctrlr = phba->phwi_ctrlr;
	phwi_context = phwi_ctrlr->phwi_ctxt;

	for (i = 0; i < phba->num_cpus; i++) {
		pbe_eq = &phwi_context->be_eq[i];
		irq_poll_init(&pbe_eq->iopoll, be_iopoll_budget, be_iopoll);
	}

	i = (phba->pcidev->msix_enabled) ? i : 0;
	/* Work item for MCC handling */
	pbe_eq = &phwi_context->be_eq[i];
	INIT_WORK(&pbe_eq->mcc_work, beiscsi_mcc_work);

	ret = beiscsi_init_irqs(phba);
	if (ret < 0) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT,
			    "BM_%d : beiscsi_dev_probe-"
			    "Failed to beiscsi_init_irqs\n");
		goto disable_iopoll;
	}
	hwi_enable_intr(phba);

	ret = iscsi_host_add(phba->shost, &phba->pcidev->dev);
	if (ret)
		goto free_irqs;

	/* set online bit after port is operational */
	set_bit(BEISCSI_HBA_ONLINE, &phba->state);
	__beiscsi_log(phba, KERN_INFO,
		      "BM_%d : port online: 0x%lx\n", phba->state);

	INIT_WORK(&phba->boot_work, beiscsi_boot_work);
	ret = beiscsi_boot_get_shandle(phba, &s_handle);
	if (ret > 0) {
		beiscsi_start_boot_work(phba, s_handle);
		/**
		 * Set this bit after starting the work to let
		 * probe handle it first.
		 * ASYNC event can too schedule this work.
		 */
		set_bit(BEISCSI_HBA_BOOT_FOUND, &phba->state);
	}

	beiscsi_iface_create_default(phba);
	schedule_delayed_work(&phba->eqd_update,
			      msecs_to_jiffies(BEISCSI_EQD_UPDATE_INTERVAL));

	INIT_WORK(&phba->sess_work, beiscsi_sess_work);
	INIT_DELAYED_WORK(&phba->recover_port, beiscsi_recover_port);
	/**
	 * Start UE detection here. UE before this will cause stall in probe
	 * and eventually fail the probe.
	 */
	timer_setup(&phba->hw_check, beiscsi_hw_health_check, 0);
	mod_timer(&phba->hw_check,
		  jiffies + msecs_to_jiffies(BEISCSI_UE_DETECT_INTERVAL));
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
		    "\n\n\n BM_%d : SUCCESS - DRIVER LOADED\n\n\n");
	return 0;

free_irqs:
	hwi_disable_intr(phba);
	beiscsi_free_irqs(phba);
disable_iopoll:
	for (i = 0; i < phba->num_cpus; i++) {
		pbe_eq = &phwi_context->be_eq[i];
		irq_poll_disable(&pbe_eq->iopoll);
	}
	destroy_workqueue(phba->wq);
free_twq:
	hwi_cleanup_port(phba);
	beiscsi_cleanup_port(phba);
	beiscsi_free_mem(phba);
free_port:
	dma_free_coherent(&phba->pcidev->dev,
			    phba->ctrl.mbox_mem_alloced.size,
			    phba->ctrl.mbox_mem_alloced.va,
			    phba->ctrl.mbox_mem_alloced.dma);
	beiscsi_unmap_pci_function(phba);
free_hba:
	pci_disable_msix(phba->pcidev);
	pci_dev_put(phba->pcidev);
	iscsi_host_free(phba->shost);
	pci_set_drvdata(pcidev, NULL);
disable_pci:
	pci_release_regions(pcidev);
	pci_disable_device(pcidev);
	return ret;
}