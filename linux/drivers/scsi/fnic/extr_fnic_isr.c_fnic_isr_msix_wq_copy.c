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
struct TYPE_3__ {int /*<<< orphan*/  isr_count; int /*<<< orphan*/  last_isr_time; } ;
struct TYPE_4__ {TYPE_1__ misc_stats; } ;
struct fnic {int /*<<< orphan*/ * intr; TYPE_2__ fnic_stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t FNIC_MSIX_WQ_COPY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 unsigned long fnic_wq_copy_cmpl_handler (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_completions ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  vnic_intr_return_credits (int /*<<< orphan*/ *,unsigned long,int,int) ; 

__attribute__((used)) static irqreturn_t fnic_isr_msix_wq_copy(int irq, void *data)
{
	struct fnic *fnic = data;
	unsigned long wq_copy_work_done = 0;

	fnic->fnic_stats.misc_stats.last_isr_time = jiffies;
	atomic64_inc(&fnic->fnic_stats.misc_stats.isr_count);

	wq_copy_work_done = fnic_wq_copy_cmpl_handler(fnic, io_completions);
	vnic_intr_return_credits(&fnic->intr[FNIC_MSIX_WQ_COPY],
				 wq_copy_work_done,
				 1 /* unmask intr */,
				 1 /* reset intr timer */);
	return IRQ_HANDLED;
}