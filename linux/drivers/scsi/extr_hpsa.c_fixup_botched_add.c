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
struct hpsa_scsi_dev_t {int dummy; } ;
struct ctlr_info {int ndevices; int /*<<< orphan*/  lock; struct hpsa_scsi_dev_t** dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hpsa_scsi_dev_t*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fixup_botched_add(struct ctlr_info *h,
	struct hpsa_scsi_dev_t *added)
{
	/* called when scsi_add_device fails in order to re-adjust
	 * h->dev[] to match the mid layer's view.
	 */
	unsigned long flags;
	int i, j;

	spin_lock_irqsave(&h->lock, flags);
	for (i = 0; i < h->ndevices; i++) {
		if (h->dev[i] == added) {
			for (j = i; j < h->ndevices-1; j++)
				h->dev[j] = h->dev[j+1];
			h->ndevices--;
			break;
		}
	}
	spin_unlock_irqrestore(&h->lock, flags);
	kfree(added);
}