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
struct snic_req_info {int /*<<< orphan*/  list; } ;
struct snic {int /*<<< orphan*/  spl_cmd_lock; int /*<<< orphan*/  snic_lock; scalar_t__ in_remove; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snic_req_free (struct snic*,struct snic_req_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
snic_release_untagged_req(struct snic *snic, struct snic_req_info *rqi)
{
	unsigned long flags;

	spin_lock_irqsave(&snic->snic_lock, flags);
	if (snic->in_remove) {
		spin_unlock_irqrestore(&snic->snic_lock, flags);
		goto end;
	}
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	spin_lock_irqsave(&snic->spl_cmd_lock, flags);
	if (list_empty(&rqi->list)) {
		spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
		goto end;
	}
	list_del_init(&rqi->list);
	spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
	snic_req_free(snic, rqi);

end:
	return;
}