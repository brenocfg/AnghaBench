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
struct hisi_sas_dq {int dummy; } ;
struct hisi_sas_device {scalar_t__ dev_type; int device_id; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; struct hisi_sas_dq* dq; struct domain_device* sas_device; struct hisi_hba* hisi_hba; int /*<<< orphan*/  dev_status; } ;
struct hisi_hba {int last_dev_id; int queue_count; int /*<<< orphan*/  lock; struct hisi_sas_device* devices; struct hisi_sas_dq* dq; } ;
struct domain_device {scalar_t__ dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_DEV_INIT ; 
 int HISI_SAS_MAX_DEVICES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ SAS_PHY_UNUSED ; 
 struct hisi_hba* dev_to_hisi_hba (struct domain_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct hisi_sas_device *hisi_sas_alloc_dev(struct domain_device *device)
{
	struct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	struct hisi_sas_device *sas_dev = NULL;
	unsigned long flags;
	int last = hisi_hba->last_dev_id;
	int first = (hisi_hba->last_dev_id + 1) % HISI_SAS_MAX_DEVICES;
	int i;

	spin_lock_irqsave(&hisi_hba->lock, flags);
	for (i = first; i != last; i %= HISI_SAS_MAX_DEVICES) {
		if (hisi_hba->devices[i].dev_type == SAS_PHY_UNUSED) {
			int queue = i % hisi_hba->queue_count;
			struct hisi_sas_dq *dq = &hisi_hba->dq[queue];

			hisi_hba->devices[i].device_id = i;
			sas_dev = &hisi_hba->devices[i];
			sas_dev->dev_status = HISI_SAS_DEV_INIT;
			sas_dev->dev_type = device->dev_type;
			sas_dev->hisi_hba = hisi_hba;
			sas_dev->sas_device = device;
			sas_dev->dq = dq;
			spin_lock_init(&sas_dev->lock);
			INIT_LIST_HEAD(&hisi_hba->devices[i].list);
			break;
		}
		i++;
	}
	hisi_hba->last_dev_id = i;
	spin_unlock_irqrestore(&hisi_hba->lock, flags);

	return sas_dev;
}