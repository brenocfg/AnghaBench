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
struct TYPE_3__ {int /*<<< orphan*/  cmpl_isr_cnt; int /*<<< orphan*/  last_isr_time; } ;
struct TYPE_4__ {TYPE_1__ misc; } ;
struct snic {int /*<<< orphan*/ * intr; TYPE_2__ s_stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 size_t SNIC_MSIX_IO_CMPL ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long snic_fwcq_cmpl_handler (struct snic*,int) ; 
 int /*<<< orphan*/  svnic_intr_return_credits (int /*<<< orphan*/ *,unsigned long,int,int) ; 

__attribute__((used)) static irqreturn_t
snic_isr_msix_io_cmpl(int irq, void *data)
{
	struct snic *snic = data;
	unsigned long iocmpl_work_done = 0;

	snic->s_stats.misc.last_isr_time = jiffies;
	atomic64_inc(&snic->s_stats.misc.cmpl_isr_cnt);

	iocmpl_work_done = snic_fwcq_cmpl_handler(snic, -1);
	svnic_intr_return_credits(&snic->intr[SNIC_MSIX_IO_CMPL],
				  iocmpl_work_done,
				  1 /* unmask intr */,
				  1 /* reset intr timer */);

	return IRQ_HANDLED;
}