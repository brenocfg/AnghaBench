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
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
struct fs_dev {TYPE_2__ tx_relq; int /*<<< orphan*/  st_q; int /*<<< orphan*/ * rx_fp; int /*<<< orphan*/ * rx_rq; TYPE_1__ hp_txq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FS_DEBUG_IRQ ; 
 int /*<<< orphan*/  FS_DEBUG_QUEUE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISR ; 
 int ISR_CSQ_W ; 
 int ISR_RBRQ0_W ; 
 int ISR_RBRQ1_W ; 
 int ISR_RBRQ2_W ; 
 int ISR_RBRQ3_W ; 
 int ISR_TBRQ_W ; 
 int /*<<< orphan*/  Q_EA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_SA (int /*<<< orphan*/ ) ; 
 int fs_debug ; 
 int /*<<< orphan*/  fs_dprintk (int,char*,...) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/ * irq_bitname ; 
 int /*<<< orphan*/  process_incoming (struct fs_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_return_queue (struct fs_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_txdone_queue (struct fs_dev*,TYPE_2__*) ; 
 int read_fs (struct fs_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  top_off_fp (struct fs_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fs_irq (int irq, void *dev_id) 
{
	int i;
	u32 status;
	struct fs_dev *dev = dev_id;

	status = read_fs (dev, ISR);
	if (!status)
		return IRQ_NONE;

	func_enter ();

#ifdef IRQ_RATE_LIMIT
	/* Aaargh! I'm ashamed. This costs more lines-of-code than the actual 
	   interrupt routine!. (Well, used to when I wrote that comment) -- REW */
	{
		static int lastjif;
		static int nintr=0;
    
		if (lastjif == jiffies) {
			if (++nintr > IRQ_RATE_LIMIT) {
				free_irq (dev->irq, dev_id);
				printk (KERN_ERR "fs: Too many interrupts. Turning off interrupt %d.\n", 
					dev->irq);
			}
		} else {
			lastjif = jiffies;
			nintr = 0;
		}
	}
#endif
	fs_dprintk (FS_DEBUG_QUEUE, "in intr: txq %d txrq %d\n", 
		    read_fs (dev, Q_EA (dev->hp_txq.offset)) -
		    read_fs (dev, Q_SA (dev->hp_txq.offset)),
		    read_fs (dev, Q_EA (dev->tx_relq.offset)) -
		    read_fs (dev, Q_SA (dev->tx_relq.offset)));

	/* print the bits in the ISR register. */
	if (fs_debug & FS_DEBUG_IRQ) {
		/* The FS_DEBUG things are unnecessary here. But this way it is
		   clear for grep that these are debug prints. */
		fs_dprintk (FS_DEBUG_IRQ,  "IRQ status:");
		for (i=0;i<27;i++) 
			if (status & (1 << i)) 
				fs_dprintk (FS_DEBUG_IRQ, " %s", irq_bitname[i]);
		fs_dprintk (FS_DEBUG_IRQ, "\n");
	}
  
	if (status & ISR_RBRQ0_W) {
		fs_dprintk (FS_DEBUG_IRQ, "Iiiin-coming (0)!!!!\n");
		process_incoming (dev, &dev->rx_rq[0]);
		/* items mentioned on RBRQ0 are from FP 0 or 1. */
		top_off_fp (dev, &dev->rx_fp[0], GFP_ATOMIC);
		top_off_fp (dev, &dev->rx_fp[1], GFP_ATOMIC);
	}

	if (status & ISR_RBRQ1_W) {
		fs_dprintk (FS_DEBUG_IRQ, "Iiiin-coming (1)!!!!\n");
		process_incoming (dev, &dev->rx_rq[1]);
		top_off_fp (dev, &dev->rx_fp[2], GFP_ATOMIC);
		top_off_fp (dev, &dev->rx_fp[3], GFP_ATOMIC);
	}

	if (status & ISR_RBRQ2_W) {
		fs_dprintk (FS_DEBUG_IRQ, "Iiiin-coming (2)!!!!\n");
		process_incoming (dev, &dev->rx_rq[2]);
		top_off_fp (dev, &dev->rx_fp[4], GFP_ATOMIC);
		top_off_fp (dev, &dev->rx_fp[5], GFP_ATOMIC);
	}

	if (status & ISR_RBRQ3_W) {
		fs_dprintk (FS_DEBUG_IRQ, "Iiiin-coming (3)!!!!\n");
		process_incoming (dev, &dev->rx_rq[3]);
		top_off_fp (dev, &dev->rx_fp[6], GFP_ATOMIC);
		top_off_fp (dev, &dev->rx_fp[7], GFP_ATOMIC);
	}

	if (status & ISR_CSQ_W) {
		fs_dprintk (FS_DEBUG_IRQ, "Command executed ok!\n");
		process_return_queue (dev, &dev->st_q);
	}

	if (status & ISR_TBRQ_W) {
		fs_dprintk (FS_DEBUG_IRQ, "Data tramsitted!\n");
		process_txdone_queue (dev, &dev->tx_relq);
	}

	func_exit ();
	return IRQ_HANDLED;
}