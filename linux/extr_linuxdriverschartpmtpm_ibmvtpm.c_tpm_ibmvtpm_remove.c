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
struct vio_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  unit_address; int /*<<< orphan*/  irq; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ crq_addr; } ;
struct ibmvtpm_dev {struct ibmvtpm_dev* rtce_buf; int /*<<< orphan*/  rtce_size; int /*<<< orphan*/  rtce_dma_handle; int /*<<< orphan*/  dev; TYPE_1__ crq_queue; int /*<<< orphan*/  crq_dma_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRQ_RES_BUF_SIZE ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int H_BUSY ; 
 int /*<<< orphan*/  H_FREE_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (int) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 

__attribute__((used)) static int tpm_ibmvtpm_remove(struct vio_dev *vdev)
{
	struct tpm_chip *chip = dev_get_drvdata(&vdev->dev);
	struct ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	int rc = 0;

	tpm_chip_unregister(chip);

	free_irq(vdev->irq, ibmvtpm);

	do {
		if (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	} while (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	dma_unmap_single(ibmvtpm->dev, ibmvtpm->crq_dma_handle,
			 CRQ_RES_BUF_SIZE, DMA_BIDIRECTIONAL);
	free_page((unsigned long)ibmvtpm->crq_queue.crq_addr);

	if (ibmvtpm->rtce_buf) {
		dma_unmap_single(ibmvtpm->dev, ibmvtpm->rtce_dma_handle,
				 ibmvtpm->rtce_size, DMA_BIDIRECTIONAL);
		kfree(ibmvtpm->rtce_buf);
	}

	kfree(ibmvtpm);
	/* For tpm_ibmvtpm_get_desired_dma */
	dev_set_drvdata(&vdev->dev, NULL);

	return 0;
}