#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sas_task {TYPE_1__* dev; } ;
struct mvs_tmf_task {int dummy; } ;
struct mvs_info {int tx_prod; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct mvs_device {struct mvs_info* mvi_info; } ;
struct completion {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* start_delivery ) (struct mvs_info*,int) ;} ;
struct TYPE_3__ {scalar_t__ lldd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 TYPE_2__* MVS_CHIP_DISP ; 
 int MVS_CHIP_SLOT_SZ ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ likely (int) ; 
 int mvs_task_prep (struct sas_task*,struct mvs_info*,int,struct mvs_tmf_task*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mvs_info*,int) ; 

__attribute__((used)) static int mvs_task_exec(struct sas_task *task, gfp_t gfp_flags,
				struct completion *completion, int is_tmf,
				struct mvs_tmf_task *tmf)
{
	struct mvs_info *mvi = NULL;
	u32 rc = 0;
	u32 pass = 0;
	unsigned long flags = 0;

	mvi = ((struct mvs_device *)task->dev->lldd_dev)->mvi_info;

	spin_lock_irqsave(&mvi->lock, flags);
	rc = mvs_task_prep(task, mvi, is_tmf, tmf, &pass);
	if (rc)
		dev_printk(KERN_ERR, mvi->dev, "mvsas exec failed[%d]!\n", rc);

	if (likely(pass))
			MVS_CHIP_DISP->start_delivery(mvi, (mvi->tx_prod - 1) &
				(MVS_CHIP_SLOT_SZ - 1));
	spin_unlock_irqrestore(&mvi->lock, flags);

	return rc;
}