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
typedef  size_t u16 ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct ibmvtpm_dev {size_t res_len; int /*<<< orphan*/  rtce_lock; scalar_t__ rtce_buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  tpm_processing_cmd; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct ibmvtpm_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tpm_ibmvtpm_recv(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	u16 len;
	int sig;

	if (!ibmvtpm->rtce_buf) {
		dev_err(ibmvtpm->dev, "ibmvtpm device is not ready\n");
		return 0;
	}

	sig = wait_event_interruptible(ibmvtpm->wq, !ibmvtpm->tpm_processing_cmd);
	if (sig)
		return -EINTR;

	len = ibmvtpm->res_len;

	if (count < len) {
		dev_err(ibmvtpm->dev,
			"Invalid size in recv: count=%zd, crq_size=%d\n",
			count, len);
		return -EIO;
	}

	spin_lock(&ibmvtpm->rtce_lock);
	memcpy((void *)buf, (void *)ibmvtpm->rtce_buf, len);
	memset(ibmvtpm->rtce_buf, 0, len);
	ibmvtpm->res_len = 0;
	spin_unlock(&ibmvtpm->rtce_lock);
	return len;
}