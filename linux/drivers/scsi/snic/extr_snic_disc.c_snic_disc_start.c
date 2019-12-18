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
struct snic_disc {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  req_cnt; } ;
struct snic {int /*<<< orphan*/  shost; int /*<<< orphan*/  snic_lock; scalar_t__ in_remove; struct snic_disc disc; } ;

/* Variables and functions */
 scalar_t__ SNIC_DISC_PENDING ; 
 int /*<<< orphan*/  SNIC_ERR (char*) ; 
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snic_queue_report_tgt_req (struct snic*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
snic_disc_start(struct snic *snic)
{
	struct snic_disc *disc = &snic->disc;
	unsigned long flags;
	int ret = 0;

	SNIC_SCSI_DBG(snic->shost, "Discovery Start.\n");

	spin_lock_irqsave(&snic->snic_lock, flags);
	if (snic->in_remove) {
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		SNIC_ERR("snic driver removal in progress ...\n");
		ret = 0;

		return ret;
	}
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	mutex_lock(&disc->mutex);
	if (disc->state == SNIC_DISC_PENDING) {
		disc->req_cnt++;
		mutex_unlock(&disc->mutex);

		return ret;
	}
	disc->state = SNIC_DISC_PENDING;
	mutex_unlock(&disc->mutex);

	ret = snic_queue_report_tgt_req(snic);
	if (ret)
		SNIC_HOST_INFO(snic->shost, "Discovery Failed, err=%d.\n", ret);

	return ret;
}