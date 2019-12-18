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
typedef  size_t u32 ;
struct sas_ha_struct {scalar_t__ lldd_ha; } ;
struct mvs_prv_info {size_t n_host; struct mvs_info** mvi; int /*<<< orphan*/  mv_tasklet; } ;
struct mvs_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {size_t (* isr_status ) (struct mvs_info*,int) ;int /*<<< orphan*/  (* isr ) (struct mvs_info*,int,size_t) ;int /*<<< orphan*/  (* interrupt_enable ) (struct mvs_info*) ;int /*<<< orphan*/  (* interrupt_disable ) (struct mvs_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 TYPE_1__* MVS_CHIP_DISP ; 
 int /*<<< orphan*/  stub1 (struct mvs_info*) ; 
 size_t stub2 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  stub3 (struct mvs_info*) ; 
 int /*<<< orphan*/  stub4 (struct mvs_info*,int,size_t) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t mvs_interrupt(int irq, void *opaque)
{
	u32 core_nr;
	u32 stat;
	struct mvs_info *mvi;
	struct sas_ha_struct *sha = opaque;
#ifndef CONFIG_SCSI_MVSAS_TASKLET
	u32 i;
#endif

	core_nr = ((struct mvs_prv_info *)sha->lldd_ha)->n_host;
	mvi = ((struct mvs_prv_info *)sha->lldd_ha)->mvi[0];

	if (unlikely(!mvi))
		return IRQ_NONE;
#ifdef CONFIG_SCSI_MVSAS_TASKLET
	MVS_CHIP_DISP->interrupt_disable(mvi);
#endif

	stat = MVS_CHIP_DISP->isr_status(mvi, irq);
	if (!stat) {
	#ifdef CONFIG_SCSI_MVSAS_TASKLET
		MVS_CHIP_DISP->interrupt_enable(mvi);
	#endif
		return IRQ_NONE;
	}

#ifdef CONFIG_SCSI_MVSAS_TASKLET
	tasklet_schedule(&((struct mvs_prv_info *)sha->lldd_ha)->mv_tasklet);
#else
	for (i = 0; i < core_nr; i++) {
		mvi = ((struct mvs_prv_info *)sha->lldd_ha)->mvi[i];
		MVS_CHIP_DISP->isr(mvi, irq, stat);
	}
#endif
	return IRQ_HANDLED;
}