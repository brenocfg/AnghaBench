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
struct ibmvtpm_dev {int tpm_processing_cmd; int /*<<< orphan*/  wq; void* res_len; int /*<<< orphan*/  vtpm_version; int /*<<< orphan*/  dev; int /*<<< orphan*/ * rtce_buf; int /*<<< orphan*/  rtce_dma_handle; void* rtce_size; } ;
struct ibmvtpm_crq {int valid; int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  IBMVTPM_VALID_CMD 134 
#define  INIT_CRQ_COMP_RES 133 
#define  INIT_CRQ_RES 132 
#define  VALID_INIT_CRQ 131 
#define  VTPM_GET_RTCE_BUFFER_SIZE_RES 130 
#define  VTPM_GET_VERSION_RES 129 
#define  VTPM_TPM_COMMAND_RES 128 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ibmvtpm_crq_send_init_complete (struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvtpm_crq_process(struct ibmvtpm_crq *crq,
				struct ibmvtpm_dev *ibmvtpm)
{
	int rc = 0;

	switch (crq->valid) {
	case VALID_INIT_CRQ:
		switch (crq->msg) {
		case INIT_CRQ_RES:
			dev_info(ibmvtpm->dev, "CRQ initialized\n");
			rc = ibmvtpm_crq_send_init_complete(ibmvtpm);
			if (rc)
				dev_err(ibmvtpm->dev, "Unable to send CRQ init complete rc=%d\n", rc);
			return;
		case INIT_CRQ_COMP_RES:
			dev_info(ibmvtpm->dev,
				 "CRQ initialization completed\n");
			return;
		default:
			dev_err(ibmvtpm->dev, "Unknown crq message type: %d\n", crq->msg);
			return;
		}
	case IBMVTPM_VALID_CMD:
		switch (crq->msg) {
		case VTPM_GET_RTCE_BUFFER_SIZE_RES:
			if (be16_to_cpu(crq->len) <= 0) {
				dev_err(ibmvtpm->dev, "Invalid rtce size\n");
				return;
			}
			ibmvtpm->rtce_size = be16_to_cpu(crq->len);
			ibmvtpm->rtce_buf = kmalloc(ibmvtpm->rtce_size,
						    GFP_ATOMIC);
			if (!ibmvtpm->rtce_buf) {
				dev_err(ibmvtpm->dev, "Failed to allocate memory for rtce buffer\n");
				return;
			}

			ibmvtpm->rtce_dma_handle = dma_map_single(ibmvtpm->dev,
				ibmvtpm->rtce_buf, ibmvtpm->rtce_size,
				DMA_BIDIRECTIONAL);

			if (dma_mapping_error(ibmvtpm->dev,
					      ibmvtpm->rtce_dma_handle)) {
				kfree(ibmvtpm->rtce_buf);
				ibmvtpm->rtce_buf = NULL;
				dev_err(ibmvtpm->dev, "Failed to dma map rtce buffer\n");
			}

			return;
		case VTPM_GET_VERSION_RES:
			ibmvtpm->vtpm_version = be32_to_cpu(crq->data);
			return;
		case VTPM_TPM_COMMAND_RES:
			/* len of the data in rtce buffer */
			ibmvtpm->res_len = be16_to_cpu(crq->len);
			ibmvtpm->tpm_processing_cmd = false;
			wake_up_interruptible(&ibmvtpm->wq);
			return;
		default:
			return;
		}
	}
	return;
}