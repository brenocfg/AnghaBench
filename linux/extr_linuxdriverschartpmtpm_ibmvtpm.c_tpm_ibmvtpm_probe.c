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
struct vio_device_id {int dummy; } ;
struct device {int dummy; } ;
struct vio_dev {int /*<<< orphan*/  unit_address; int /*<<< orphan*/  irq; struct device dev; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct ibmvtpm_crq_queue {int num_entry; struct ibmvtpm_crq* crq_addr; scalar_t__ index; } ;
struct ibmvtpm_dev {int /*<<< orphan*/  crq_dma_handle; int /*<<< orphan*/  rtce_lock; int /*<<< orphan*/  wq; struct ibmvtpm_crq_queue crq_queue; struct vio_dev* vdev; struct device* dev; } ;
struct ibmvtpm_crq {int dummy; } ;

/* Variables and functions */
 int CRQ_RES_BUF_SIZE ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int H_BUSY ; 
 int /*<<< orphan*/  H_FREE_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (int) ; 
 int /*<<< orphan*/  H_REG_CRQ ; 
 int H_RESOURCE ; 
 scalar_t__ IS_ERR (struct tpm_chip*) ; 
 int PTR_ERR (struct tpm_chip*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,struct ibmvtpm_crq*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int ibmvtpm_crq_get_rtce_size (struct ibmvtpm_dev*) ; 
 int ibmvtpm_crq_get_version (struct ibmvtpm_dev*) ; 
 int ibmvtpm_crq_send_init (struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  ibmvtpm_interrupt ; 
 int ibmvtpm_reset_crq (struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ibmvtpm_dev*) ; 
 struct ibmvtpm_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int tpm_chip_register (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_ibmvtpm ; 
 int /*<<< orphan*/  tpm_ibmvtpm_driver_name ; 
 struct tpm_chip* tpmm_chip_alloc (struct device*,int /*<<< orphan*/ *) ; 
 int vio_enable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static int tpm_ibmvtpm_probe(struct vio_dev *vio_dev,
				   const struct vio_device_id *id)
{
	struct ibmvtpm_dev *ibmvtpm;
	struct device *dev = &vio_dev->dev;
	struct ibmvtpm_crq_queue *crq_q;
	struct tpm_chip *chip;
	int rc = -ENOMEM, rc1;

	chip = tpmm_chip_alloc(dev, &tpm_ibmvtpm);
	if (IS_ERR(chip))
		return PTR_ERR(chip);

	ibmvtpm = kzalloc(sizeof(struct ibmvtpm_dev), GFP_KERNEL);
	if (!ibmvtpm) {
		dev_err(dev, "kzalloc for ibmvtpm failed\n");
		goto cleanup;
	}

	ibmvtpm->dev = dev;
	ibmvtpm->vdev = vio_dev;

	crq_q = &ibmvtpm->crq_queue;
	crq_q->crq_addr = (struct ibmvtpm_crq *)get_zeroed_page(GFP_KERNEL);
	if (!crq_q->crq_addr) {
		dev_err(dev, "Unable to allocate memory for crq_addr\n");
		goto cleanup;
	}

	crq_q->num_entry = CRQ_RES_BUF_SIZE / sizeof(*crq_q->crq_addr);
	ibmvtpm->crq_dma_handle = dma_map_single(dev, crq_q->crq_addr,
						 CRQ_RES_BUF_SIZE,
						 DMA_BIDIRECTIONAL);

	if (dma_mapping_error(dev, ibmvtpm->crq_dma_handle)) {
		dev_err(dev, "dma mapping failed\n");
		goto cleanup;
	}

	rc = plpar_hcall_norets(H_REG_CRQ, vio_dev->unit_address,
				ibmvtpm->crq_dma_handle, CRQ_RES_BUF_SIZE);
	if (rc == H_RESOURCE)
		rc = ibmvtpm_reset_crq(ibmvtpm);

	if (rc) {
		dev_err(dev, "Unable to register CRQ rc=%d\n", rc);
		goto reg_crq_cleanup;
	}

	rc = request_irq(vio_dev->irq, ibmvtpm_interrupt, 0,
			 tpm_ibmvtpm_driver_name, ibmvtpm);
	if (rc) {
		dev_err(dev, "Error %d register irq 0x%x\n", rc, vio_dev->irq);
		goto init_irq_cleanup;
	}

	rc = vio_enable_interrupts(vio_dev);
	if (rc) {
		dev_err(dev, "Error %d enabling interrupts\n", rc);
		goto init_irq_cleanup;
	}

	init_waitqueue_head(&ibmvtpm->wq);

	crq_q->index = 0;

	dev_set_drvdata(&chip->dev, ibmvtpm);

	spin_lock_init(&ibmvtpm->rtce_lock);

	rc = ibmvtpm_crq_send_init(ibmvtpm);
	if (rc)
		goto init_irq_cleanup;

	rc = ibmvtpm_crq_get_version(ibmvtpm);
	if (rc)
		goto init_irq_cleanup;

	rc = ibmvtpm_crq_get_rtce_size(ibmvtpm);
	if (rc)
		goto init_irq_cleanup;

	return tpm_chip_register(chip);
init_irq_cleanup:
	do {
		rc1 = plpar_hcall_norets(H_FREE_CRQ, vio_dev->unit_address);
	} while (rc1 == H_BUSY || H_IS_LONG_BUSY(rc1));
reg_crq_cleanup:
	dma_unmap_single(dev, ibmvtpm->crq_dma_handle, CRQ_RES_BUF_SIZE,
			 DMA_BIDIRECTIONAL);
cleanup:
	if (ibmvtpm) {
		if (crq_q->crq_addr)
			free_page((unsigned long)crq_q->crq_addr);
		kfree(ibmvtpm);
	}

	return rc;
}