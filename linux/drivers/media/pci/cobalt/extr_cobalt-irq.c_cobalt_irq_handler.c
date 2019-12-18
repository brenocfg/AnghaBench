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
typedef  int u32 ;
struct cobalt_stream {unsigned int dma_fifo_mask; int dma_channel; int adv_irq_mask; int /*<<< orphan*/  q; int /*<<< orphan*/  flags; scalar_t__ is_audio; } ;
struct cobalt {int /*<<< orphan*/  irq_none; int /*<<< orphan*/  irq_dma_tot; int /*<<< orphan*/  irq_advout; int /*<<< orphan*/  irq_adv2; int /*<<< orphan*/  irq_adv1; int /*<<< orphan*/  irq_work_queue; int /*<<< orphan*/  irq_work_queues; int /*<<< orphan*/  irq_full_fifo; int /*<<< orphan*/ * irq_dma; struct cobalt_stream* streams; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int COBALT_NUM_STREAMS ; 
 int /*<<< orphan*/  COBALT_STREAM_FL_ADV_IRQ ; 
 int COBALT_SYSSTAT_VI0_INT1_MSK ; 
 int COBALT_SYSSTAT_VI0_INT2_MSK ; 
 int COBALT_SYSSTAT_VI1_INT1_MSK ; 
 int COBALT_SYSSTAT_VI1_INT2_MSK ; 
 int COBALT_SYSSTAT_VI2_INT1_MSK ; 
 int COBALT_SYSSTAT_VI2_INT2_MSK ; 
 int COBALT_SYSSTAT_VI3_INT1_MSK ; 
 int COBALT_SYSSTAT_VI3_INT2_MSK ; 
 int COBALT_SYSSTAT_VIHSMA_INT1_MSK ; 
 int COBALT_SYSSTAT_VIHSMA_INT2_MSK ; 
 int COBALT_SYSSTAT_VOHSMA_INT1_MSK ; 
 int /*<<< orphan*/  COBALT_SYS_STAT_EDGE ; 
 int /*<<< orphan*/  COBALT_SYS_STAT_MASK ; 
 int /*<<< orphan*/  DMA_INTERRUPT_STATUS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cobalt_dma_stream_queue_handler (struct cobalt_stream*) ; 
 int /*<<< orphan*/  cobalt_info (char*,int) ; 
 int cobalt_read_bar0 (struct cobalt*,int /*<<< orphan*/ ) ; 
 int cobalt_read_bar1 (struct cobalt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cobalt_write_bar0 (struct cobalt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cobalt_write_bar1 (struct cobalt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ *) ; 

irqreturn_t cobalt_irq_handler(int irq, void *dev_id)
{
	struct cobalt *cobalt = (struct cobalt *)dev_id;
	u32 dma_interrupt =
		cobalt_read_bar0(cobalt, DMA_INTERRUPT_STATUS_REG) & 0xffff;
	u32 mask = cobalt_read_bar1(cobalt, COBALT_SYS_STAT_MASK);
	u32 edge = cobalt_read_bar1(cobalt, COBALT_SYS_STAT_EDGE);
	int i;

	/* Clear DMA interrupt */
	cobalt_write_bar0(cobalt, DMA_INTERRUPT_STATUS_REG, dma_interrupt);
	cobalt_write_bar1(cobalt, COBALT_SYS_STAT_MASK, mask & ~edge);
	cobalt_write_bar1(cobalt, COBALT_SYS_STAT_EDGE, edge);

	for (i = 0; i < COBALT_NUM_STREAMS; i++) {
		struct cobalt_stream *s = &cobalt->streams[i];
		unsigned dma_fifo_mask = s->dma_fifo_mask;

		if (dma_interrupt & (1 << s->dma_channel)) {
			cobalt->irq_dma[i]++;
			/* Give fresh buffer to user and chain newly
			 * queued buffers */
			cobalt_dma_stream_queue_handler(s);
			if (!s->is_audio) {
				edge &= ~dma_fifo_mask;
				cobalt_write_bar1(cobalt, COBALT_SYS_STAT_MASK,
						  mask & ~edge);
			}
		}
		if (s->is_audio)
			continue;
		if (edge & s->adv_irq_mask)
			set_bit(COBALT_STREAM_FL_ADV_IRQ, &s->flags);
		if ((edge & mask & dma_fifo_mask) && vb2_is_streaming(&s->q)) {
			cobalt_info("full rx FIFO %d\n", i);
			cobalt->irq_full_fifo++;
		}
	}

	queue_work(cobalt->irq_work_queues, &cobalt->irq_work_queue);

	if (edge & mask & (COBALT_SYSSTAT_VI0_INT1_MSK |
			   COBALT_SYSSTAT_VI1_INT1_MSK |
			   COBALT_SYSSTAT_VI2_INT1_MSK |
			   COBALT_SYSSTAT_VI3_INT1_MSK |
			   COBALT_SYSSTAT_VIHSMA_INT1_MSK |
			   COBALT_SYSSTAT_VOHSMA_INT1_MSK))
		cobalt->irq_adv1++;
	if (edge & mask & (COBALT_SYSSTAT_VI0_INT2_MSK |
			   COBALT_SYSSTAT_VI1_INT2_MSK |
			   COBALT_SYSSTAT_VI2_INT2_MSK |
			   COBALT_SYSSTAT_VI3_INT2_MSK |
			   COBALT_SYSSTAT_VIHSMA_INT2_MSK))
		cobalt->irq_adv2++;
	if (edge & mask & COBALT_SYSSTAT_VOHSMA_INT1_MSK)
		cobalt->irq_advout++;
	if (dma_interrupt)
		cobalt->irq_dma_tot++;
	if (!(edge & mask) && !dma_interrupt)
		cobalt->irq_none++;
	dma_interrupt = cobalt_read_bar0(cobalt, DMA_INTERRUPT_STATUS_REG);

	return IRQ_HANDLED;
}