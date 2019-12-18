#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int device; int devfn; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct megasas_instance {int unique_id; scalar_t__ adapter_type; struct pci_dev* pdev; scalar_t__ msix_vectors; TYPE_3__* instancet; scalar_t__ requestorId; TYPE_2__* host_device_list_buf; int /*<<< orphan*/  enable_fw_dev_list; scalar_t__ unload; void* vf_affiliation; int /*<<< orphan*/  vf_affiliation_h; void* vf_affiliation_111; int /*<<< orphan*/  vf_affiliation_111_h; scalar_t__ PlasmaFW111; int /*<<< orphan*/  init_id; struct Scsi_Host* host; int /*<<< orphan*/  fw_reset_no_pci_access; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct MR_LD_VF_AFFILIATION_111 {int dummy; } ;
struct MR_LD_VF_AFFILIATION {int dummy; } ;
struct TYPE_8__ {size_t max_index; struct megasas_instance** instance; int /*<<< orphan*/  count; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* disable_intr ) (struct megasas_instance*) ;} ;
struct TYPE_6__ {scalar_t__ count; } ;
struct TYPE_5__ {int number; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int MAX_LOGICAL_DRIVES ; 
 int /*<<< orphan*/  MEGASAS_DEFAULT_INIT_ID ; 
 scalar_t__ MFI_SERIES ; 
 int /*<<< orphan*/  PCI_CAP_ID_MSIX ; 
#define  PCI_DEVICE_ID_LSI_AERO_10E0 133 
#define  PCI_DEVICE_ID_LSI_AERO_10E1 132 
#define  PCI_DEVICE_ID_LSI_AERO_10E3 131 
#define  PCI_DEVICE_ID_LSI_AERO_10E4 130 
#define  PCI_DEVICE_ID_LSI_AERO_10E5 129 
#define  PCI_DEVICE_ID_LSI_AERO_10E7 128 
 scalar_t__ PCI_MSIX_FLAGS ; 
 int PCI_MSIX_FLAGS_ENABLE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_destroy_irqs (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_get_ld_vf_affiliation (struct megasas_instance*,int) ; 
 scalar_t__ megasas_init_fw (struct megasas_instance*) ; 
 scalar_t__ megasas_io_attach (struct megasas_instance*) ; 
 TYPE_4__ megasas_mgmt_info ; 
 int /*<<< orphan*/  megasas_release_fusion (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_release_mfi (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_set_adapter_type (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_setup_debugfs (struct megasas_instance*) ; 
 scalar_t__ megasas_start_aen (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_template ; 
 int /*<<< orphan*/  memset (struct megasas_instance*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct megasas_instance*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 scalar_t__ reset_devices ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct megasas_instance*) ; 

__attribute__((used)) static int megasas_probe_one(struct pci_dev *pdev,
			     const struct pci_device_id *id)
{
	int rval, pos;
	struct Scsi_Host *host;
	struct megasas_instance *instance;
	u16 control = 0;

	switch (pdev->device) {
	case PCI_DEVICE_ID_LSI_AERO_10E0:
	case PCI_DEVICE_ID_LSI_AERO_10E3:
	case PCI_DEVICE_ID_LSI_AERO_10E4:
	case PCI_DEVICE_ID_LSI_AERO_10E7:
		dev_err(&pdev->dev, "Adapter is in non secure mode\n");
		return 1;
	case PCI_DEVICE_ID_LSI_AERO_10E1:
	case PCI_DEVICE_ID_LSI_AERO_10E5:
		dev_info(&pdev->dev, "Adapter is in configurable secure mode\n");
		break;
	}

	/* Reset MSI-X in the kdump kernel */
	if (reset_devices) {
		pos = pci_find_capability(pdev, PCI_CAP_ID_MSIX);
		if (pos) {
			pci_read_config_word(pdev, pos + PCI_MSIX_FLAGS,
					     &control);
			if (control & PCI_MSIX_FLAGS_ENABLE) {
				dev_info(&pdev->dev, "resetting MSI-X\n");
				pci_write_config_word(pdev,
						      pos + PCI_MSIX_FLAGS,
						      control &
						      ~PCI_MSIX_FLAGS_ENABLE);
			}
		}
	}

	/*
	 * PCI prepping: enable device set bus mastering and dma mask
	 */
	rval = pci_enable_device_mem(pdev);

	if (rval) {
		return rval;
	}

	pci_set_master(pdev);

	host = scsi_host_alloc(&megasas_template,
			       sizeof(struct megasas_instance));

	if (!host) {
		dev_printk(KERN_DEBUG, &pdev->dev, "scsi_host_alloc failed\n");
		goto fail_alloc_instance;
	}

	instance = (struct megasas_instance *)host->hostdata;
	memset(instance, 0, sizeof(*instance));
	atomic_set(&instance->fw_reset_no_pci_access, 0);

	/*
	 * Initialize PCI related and misc parameters
	 */
	instance->pdev = pdev;
	instance->host = host;
	instance->unique_id = pdev->bus->number << 8 | pdev->devfn;
	instance->init_id = MEGASAS_DEFAULT_INIT_ID;

	megasas_set_adapter_type(instance);

	/*
	 * Initialize MFI Firmware
	 */
	if (megasas_init_fw(instance))
		goto fail_init_mfi;

	if (instance->requestorId) {
		if (instance->PlasmaFW111) {
			instance->vf_affiliation_111 =
				dma_alloc_coherent(&pdev->dev,
					sizeof(struct MR_LD_VF_AFFILIATION_111),
					&instance->vf_affiliation_111_h,
					GFP_KERNEL);
			if (!instance->vf_affiliation_111)
				dev_warn(&pdev->dev, "Can't allocate "
				       "memory for VF affiliation buffer\n");
		} else {
			instance->vf_affiliation =
				dma_alloc_coherent(&pdev->dev,
					(MAX_LOGICAL_DRIVES + 1) *
					sizeof(struct MR_LD_VF_AFFILIATION),
					&instance->vf_affiliation_h,
					GFP_KERNEL);
			if (!instance->vf_affiliation)
				dev_warn(&pdev->dev, "Can't allocate "
				       "memory for VF affiliation buffer\n");
		}
	}

	/*
	 * Store instance in PCI softstate
	 */
	pci_set_drvdata(pdev, instance);

	/*
	 * Add this controller to megasas_mgmt_info structure so that it
	 * can be exported to management applications
	 */
	megasas_mgmt_info.count++;
	megasas_mgmt_info.instance[megasas_mgmt_info.max_index] = instance;
	megasas_mgmt_info.max_index++;

	/*
	 * Register with SCSI mid-layer
	 */
	if (megasas_io_attach(instance))
		goto fail_io_attach;

	instance->unload = 0;
	/*
	 * Trigger SCSI to scan our drives
	 */
	if (!instance->enable_fw_dev_list ||
	    (instance->host_device_list_buf->count > 0))
		scsi_scan_host(host);

	/*
	 * Initiate AEN (Asynchronous Event Notification)
	 */
	if (megasas_start_aen(instance)) {
		dev_printk(KERN_DEBUG, &pdev->dev, "start aen failed\n");
		goto fail_start_aen;
	}

	megasas_setup_debugfs(instance);

	/* Get current SR-IOV LD/VF affiliation */
	if (instance->requestorId)
		megasas_get_ld_vf_affiliation(instance, 1);

	return 0;

fail_start_aen:
fail_io_attach:
	megasas_mgmt_info.count--;
	megasas_mgmt_info.max_index--;
	megasas_mgmt_info.instance[megasas_mgmt_info.max_index] = NULL;

	instance->instancet->disable_intr(instance);
	megasas_destroy_irqs(instance);

	if (instance->adapter_type != MFI_SERIES)
		megasas_release_fusion(instance);
	else
		megasas_release_mfi(instance);
	if (instance->msix_vectors)
		pci_free_irq_vectors(instance->pdev);
fail_init_mfi:
	scsi_host_put(host);
fail_alloc_instance:
	pci_disable_device(pdev);

	return -ENODEV;
}