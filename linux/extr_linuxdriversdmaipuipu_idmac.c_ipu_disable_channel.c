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
typedef  unsigned long uint32_t ;
struct ipu {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int chan_id; } ;
struct idmac_channel {int /*<<< orphan*/  eof_irq; TYPE_1__ dma_chan; } ;
struct idmac {int dummy; } ;
typedef  enum ipu_channel { ____Placeholder_ipu_channel } ipu_channel ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAC_CHA_BUSY ; 
 int /*<<< orphan*/  IDMAC_CHA_EN ; 
 int IDMAC_SDC_0 ; 
 int IDMAC_SDC_1 ; 
 int /*<<< orphan*/  IPU_CHA_BUF0_RDY ; 
 int /*<<< orphan*/  IPU_CHA_BUF1_RDY ; 
 int /*<<< orphan*/  IPU_TASKS_STAT ; 
 scalar_t__ TASK_STAT_ACTIVE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 unsigned long idmac_read_icreg (struct ipu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_read_ipureg (struct ipu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_write_icreg (struct ipu*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ ipu_channel_status (struct ipu*,int) ; 
 int /*<<< orphan*/  ipu_ic_disable_task (struct ipu*,int) ; 
 int /*<<< orphan*/  ipu_irq_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ipu* to_ipu (struct idmac*) ; 

__attribute__((used)) static int ipu_disable_channel(struct idmac *idmac, struct idmac_channel *ichan,
			       bool wait_for_stop)
{
	enum ipu_channel channel = ichan->dma_chan.chan_id;
	struct ipu *ipu = to_ipu(idmac);
	uint32_t reg;
	unsigned long flags;
	unsigned long chan_mask = 1UL << channel;
	unsigned int timeout;

	if (wait_for_stop && channel != IDMAC_SDC_1 && channel != IDMAC_SDC_0) {
		timeout = 40;
		/* This waiting always fails. Related to spurious irq problem */
		while ((idmac_read_icreg(ipu, IDMAC_CHA_BUSY) & chan_mask) ||
		       (ipu_channel_status(ipu, channel) == TASK_STAT_ACTIVE)) {
			timeout--;
			msleep(10);

			if (!timeout) {
				dev_dbg(ipu->dev,
					"Warning: timeout waiting for channel %u to "
					"stop: buf0_rdy = 0x%08X, buf1_rdy = 0x%08X, "
					"busy = 0x%08X, tstat = 0x%08X\n", channel,
					idmac_read_ipureg(ipu, IPU_CHA_BUF0_RDY),
					idmac_read_ipureg(ipu, IPU_CHA_BUF1_RDY),
					idmac_read_icreg(ipu, IDMAC_CHA_BUSY),
					idmac_read_ipureg(ipu, IPU_TASKS_STAT));
				break;
			}
		}
		dev_dbg(ipu->dev, "timeout = %d * 10ms\n", 40 - timeout);
	}
	/* SDC BG and FG must be disabled before DMA is disabled */
	if (wait_for_stop && (channel == IDMAC_SDC_0 ||
			      channel == IDMAC_SDC_1)) {
		for (timeout = 5;
		     timeout && !ipu_irq_status(ichan->eof_irq); timeout--)
			msleep(5);
	}

	spin_lock_irqsave(&ipu->lock, flags);

	/* Disable IC task */
	ipu_ic_disable_task(ipu, channel);

	/* Disable DMA channel(s) */
	reg = idmac_read_icreg(ipu, IDMAC_CHA_EN);
	idmac_write_icreg(ipu, reg & ~chan_mask, IDMAC_CHA_EN);

	spin_unlock_irqrestore(&ipu->lock, flags);

	return 0;
}