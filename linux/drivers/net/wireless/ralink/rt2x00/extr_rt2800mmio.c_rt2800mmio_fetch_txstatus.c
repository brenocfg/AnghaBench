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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/  irqmask_lock; int /*<<< orphan*/  txstatus_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_STA_FIFO ; 
 int /*<<< orphan*/  TX_STA_FIFO_VALID ; 
 int /*<<< orphan*/  kfifo_is_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rt2800mmio_fetch_txstatus(struct rt2x00_dev *rt2x00dev)
{
	u32 status;
	unsigned long flags;

	/*
	 * The TX_FIFO_STATUS interrupt needs special care. We should
	 * read TX_STA_FIFO but we should do it immediately as otherwise
	 * the register can overflow and we would lose status reports.
	 *
	 * Hence, read the TX_STA_FIFO register and copy all tx status
	 * reports into a kernel FIFO which is handled in the txstatus
	 * tasklet. We use a tasklet to process the tx status reports
	 * because we can schedule the tasklet multiple times (when the
	 * interrupt fires again during tx status processing).
	 *
	 * We also read statuses from tx status timeout timer, use
	 * lock to prevent concurent writes to fifo.
	 */

	spin_lock_irqsave(&rt2x00dev->irqmask_lock, flags);

	while (!kfifo_is_full(&rt2x00dev->txstatus_fifo)) {
		status = rt2x00mmio_register_read(rt2x00dev, TX_STA_FIFO);
		if (!rt2x00_get_field32(status, TX_STA_FIFO_VALID))
			break;

		kfifo_put(&rt2x00dev->txstatus_fifo, status);
	}

	spin_unlock_irqrestore(&rt2x00dev->irqmask_lock, flags);
}