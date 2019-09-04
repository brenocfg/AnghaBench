#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_22__ {int flags; } ;
struct TYPE_20__ {int /*<<< orphan*/  txok; int /*<<< orphan*/  txunder; int /*<<< orphan*/  txabort; int /*<<< orphan*/  brk; int /*<<< orphan*/  exithunt; } ;
struct TYPE_19__ {scalar_t__ mode; } ;
struct TYPE_21__ {int irq_occurred; int bh_requested; int /*<<< orphan*/  irq_level; int /*<<< orphan*/  lock; int /*<<< orphan*/  task; int /*<<< orphan*/  device_name; int /*<<< orphan*/  bh_running; scalar_t__ pending_bh; TYPE_3__ icount; scalar_t__ tx_aborting; TYPE_2__ params; TYPE_7__ port; int /*<<< orphan*/  event_wait_q; TYPE_1__* p_dev; } ;
struct TYPE_18__ {int /*<<< orphan*/  _locked; } ;
typedef  TYPE_4__ MGSLPC_INFO ;

/* Variables and functions */
 int ASYNC_SAK ; 
 unsigned char BIT0 ; 
 unsigned char BIT1 ; 
 unsigned char BIT2 ; 
 unsigned char BIT3 ; 
 unsigned char BIT7 ; 
 scalar_t__ CHA ; 
 scalar_t__ CHB ; 
 int /*<<< orphan*/  CMD_RXFIFO_READ ; 
 scalar_t__ DEBUG_LEVEL_ISR ; 
 scalar_t__ GIS ; 
 unsigned short IRQ_ALLSENT ; 
 unsigned short IRQ_BREAK_ON ; 
 unsigned short IRQ_CTS ; 
 unsigned short IRQ_DCD ; 
 unsigned short IRQ_EXITHUNT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned short IRQ_RXEOM ; 
 unsigned short IRQ_RXFIFO ; 
 unsigned short IRQ_RXTIME ; 
 unsigned short IRQ_TIMER ; 
 unsigned short IRQ_TXFIFO ; 
 unsigned short IRQ_UNDERRUN ; 
 scalar_t__ ISR ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ PIS ; 
 int /*<<< orphan*/  cts_change (TYPE_4__*,struct tty_struct*) ; 
 int /*<<< orphan*/  dcd_change (TYPE_4__*,struct tty_struct*) ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  do_SAK (struct tty_struct*) ; 
 int /*<<< orphan*/  dsr_change (TYPE_4__*) ; 
 int /*<<< orphan*/  irq_disable (TYPE_4__*,scalar_t__,unsigned short) ; 
 int /*<<< orphan*/  issue_command (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned char read_reg (TYPE_4__*,scalar_t__) ; 
 unsigned short read_reg16 (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  ri_change (TYPE_4__*) ; 
 int /*<<< orphan*/  rx_ready_async (TYPE_4__*,unsigned short) ; 
 int /*<<< orphan*/  rx_ready_hdlc (TYPE_4__*,unsigned short) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_7__*) ; 
 int /*<<< orphan*/  tx_done (TYPE_4__*,struct tty_struct*) ; 
 int /*<<< orphan*/  tx_ready (TYPE_4__*,struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mgslpc_isr(int dummy, void *dev_id)
{
	MGSLPC_INFO *info = dev_id;
	struct tty_struct *tty;
	unsigned short isr;
	unsigned char gis, pis;
	int count=0;

	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("mgslpc_isr(%d) entry.\n", info->irq_level);

	if (!(info->p_dev->_locked))
		return IRQ_HANDLED;

	tty = tty_port_tty_get(&info->port);

	spin_lock(&info->lock);

	while ((gis = read_reg(info, CHA + GIS))) {
		if (debug_level >= DEBUG_LEVEL_ISR)
			printk("mgslpc_isr %s gis=%04X\n", info->device_name,gis);

		if ((gis & 0x70) || count > 1000) {
			printk("synclink_cs:hardware failed or ejected\n");
			break;
		}
		count++;

		if (gis & (BIT1 | BIT0)) {
			isr = read_reg16(info, CHB + ISR);
			if (isr & IRQ_DCD)
				dcd_change(info, tty);
			if (isr & IRQ_CTS)
				cts_change(info, tty);
		}
		if (gis & (BIT3 | BIT2))
		{
			isr = read_reg16(info, CHA + ISR);
			if (isr & IRQ_TIMER) {
				info->irq_occurred = true;
				irq_disable(info, CHA, IRQ_TIMER);
			}

			/* receive IRQs */
			if (isr & IRQ_EXITHUNT) {
				info->icount.exithunt++;
				wake_up_interruptible(&info->event_wait_q);
			}
			if (isr & IRQ_BREAK_ON) {
				info->icount.brk++;
				if (info->port.flags & ASYNC_SAK)
					do_SAK(tty);
			}
			if (isr & IRQ_RXTIME) {
				issue_command(info, CHA, CMD_RXFIFO_READ);
			}
			if (isr & (IRQ_RXEOM | IRQ_RXFIFO)) {
				if (info->params.mode == MGSL_MODE_HDLC)
					rx_ready_hdlc(info, isr & IRQ_RXEOM);
				else
					rx_ready_async(info, isr & IRQ_RXEOM);
			}

			/* transmit IRQs */
			if (isr & IRQ_UNDERRUN) {
				if (info->tx_aborting)
					info->icount.txabort++;
				else
					info->icount.txunder++;
				tx_done(info, tty);
			}
			else if (isr & IRQ_ALLSENT) {
				info->icount.txok++;
				tx_done(info, tty);
			}
			else if (isr & IRQ_TXFIFO)
				tx_ready(info, tty);
		}
		if (gis & BIT7) {
			pis = read_reg(info, CHA + PIS);
			if (pis & BIT1)
				dsr_change(info);
			if (pis & BIT2)
				ri_change(info);
		}
	}

	/* Request bottom half processing if there's something
	 * for it to do and the bh is not already running
	 */

	if (info->pending_bh && !info->bh_running && !info->bh_requested) {
		if (debug_level >= DEBUG_LEVEL_ISR)
			printk("%s(%d):%s queueing bh task.\n",
				__FILE__,__LINE__,info->device_name);
		schedule_work(&info->task);
		info->bh_requested = true;
	}

	spin_unlock(&info->lock);
	tty_kref_put(tty);

	if (debug_level >= DEBUG_LEVEL_ISR)
		printk("%s(%d):mgslpc_isr(%d)exit.\n",
		       __FILE__, __LINE__, info->irq_level);

	return IRQ_HANDLED;
}