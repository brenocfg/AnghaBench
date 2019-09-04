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
typedef  int /*<<< orphan*/  u8 ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct ibmvtpm_dev {size_t rtce_size; int tpm_processing_cmd; int /*<<< orphan*/  rtce_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  rtce_dma_handle; int /*<<< orphan*/  vdev; scalar_t__ rtce_buf; scalar_t__ res_len; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int H_SUCCESS ; 
 int /*<<< orphan*/  IBMVTPM_VALID_CMD ; 
 int /*<<< orphan*/  VTPM_TPM_COMMAND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct ibmvtpm_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int ibmvtpm_send_crq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tpm_ibmvtpm_send(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	int rc, sig;

	if (!ibmvtpm->rtce_buf) {
		dev_err(ibmvtpm->dev, "ibmvtpm device is not ready\n");
		return 0;
	}

	if (count > ibmvtpm->rtce_size) {
		dev_err(ibmvtpm->dev,
			"Invalid size in send: count=%zd, rtce_size=%d\n",
			count, ibmvtpm->rtce_size);
		return -EIO;
	}

	if (ibmvtpm->tpm_processing_cmd) {
		dev_info(ibmvtpm->dev,
		         "Need to wait for TPM to finish\n");
		/* wait for previous command to finish */
		sig = wait_event_interruptible(ibmvtpm->wq, !ibmvtpm->tpm_processing_cmd);
		if (sig)
			return -EINTR;
	}

	spin_lock(&ibmvtpm->rtce_lock);
	ibmvtpm->res_len = 0;
	memcpy((void *)ibmvtpm->rtce_buf, (void *)buf, count);

	/*
	 * set the processing flag before the Hcall, since we may get the
	 * result (interrupt) before even being able to check rc.
	 */
	ibmvtpm->tpm_processing_cmd = true;

	rc = ibmvtpm_send_crq(ibmvtpm->vdev,
			IBMVTPM_VALID_CMD, VTPM_TPM_COMMAND,
			count, ibmvtpm->rtce_dma_handle);
	if (rc != H_SUCCESS) {
		dev_err(ibmvtpm->dev, "tpm_ibmvtpm_send failed rc=%d\n", rc);
		rc = 0;
		ibmvtpm->tpm_processing_cmd = false;
	} else
		rc = 0;

	spin_unlock(&ibmvtpm->rtce_lock);
	return rc;
}