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
typedef  int u32 ;
struct seq_file {struct dwc3_ep* private; } ;
struct dwc3_ep {struct dwc3* dwc; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwparams0; } ;
struct dwc3 {int /*<<< orphan*/  lock; TYPE_1__ hwparams; } ;

/* Variables and functions */
 int DWC3_MDWIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_TXFIFO ; 
 int dwc3_core_fifo_space (struct dwc3_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc3_tx_fifo_size_show(struct seq_file *s, void *unused)
{
	struct dwc3_ep		*dep = s->private;
	struct dwc3		*dwc = dep->dwc;
	unsigned long		flags;
	u32			val;

	spin_lock_irqsave(&dwc->lock, flags);
	val = dwc3_core_fifo_space(dep, DWC3_TXFIFO);

	/* Convert to bytes */
	val *= DWC3_MDWIDTH(dwc->hwparams.hwparams0);
	val >>= 3;
	seq_printf(s, "%u\n", val);
	spin_unlock_irqrestore(&dwc->lock, flags);

	return 0;
}