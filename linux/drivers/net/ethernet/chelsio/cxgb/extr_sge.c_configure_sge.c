#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sge_params {int dummy; } ;
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  dma_addr; } ;
struct sge {int sge_control; int intrtimer_nres; int /*<<< orphan*/  rx_pkt_pad; TYPE_3__ respQ; TYPE_2__* freelQ; TYPE_1__* cmdQ; struct adapter* adapter; } ;
struct adapter {scalar_t__ regs; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CMD0BASELWR ; 
 int /*<<< orphan*/  A_SG_CMD0BASEUPR ; 
 int /*<<< orphan*/  A_SG_CMD0SIZE ; 
 int /*<<< orphan*/  A_SG_CMD1BASELWR ; 
 int /*<<< orphan*/  A_SG_CMD1BASEUPR ; 
 int /*<<< orphan*/  A_SG_CMD1SIZE ; 
 scalar_t__ A_SG_CONTROL ; 
 int /*<<< orphan*/  A_SG_FL0BASELWR ; 
 int /*<<< orphan*/  A_SG_FL0BASEUPR ; 
 int /*<<< orphan*/  A_SG_FL0SIZE ; 
 int /*<<< orphan*/  A_SG_FL1BASELWR ; 
 int /*<<< orphan*/  A_SG_FL1BASEUPR ; 
 int /*<<< orphan*/  A_SG_FL1SIZE ; 
 scalar_t__ A_SG_FLTHRESHOLD ; 
 int /*<<< orphan*/  A_SG_RSPBASELWR ; 
 int /*<<< orphan*/  A_SG_RSPBASEUPR ; 
 scalar_t__ A_SG_RSPQUEUECREDIT ; 
 int /*<<< orphan*/  A_SG_RSPSIZE ; 
 int F_CMDQ0_ENABLE ; 
 int F_CMDQ1_ENABLE ; 
 int F_CPL_ENABLE ; 
 int F_DISABLE_CMDQ1_GTS ; 
 int F_ENABLE_BIG_ENDIAN ; 
 int F_FL0_ENABLE ; 
 int F_FL1_ENABLE ; 
 int F_ISCSI_COALESCE ; 
 int F_RESPONSE_QUEUE_ENABLE ; 
 int SGE_INTRTIMER_NRES ; 
 scalar_t__ SGE_RX_SM_BUF_SIZE ; 
 int V_CMDQ_PRIORITY (int) ; 
 int V_RX_PKT_OFFSET (int /*<<< orphan*/ ) ; 
 int core_ticks_per_usec (struct adapter*) ; 
 int /*<<< orphan*/  setup_ring_params (struct adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_sge_set_coalesce_params (struct sge*,struct sge_params*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void configure_sge(struct sge *sge, struct sge_params *p)
{
	struct adapter *ap = sge->adapter;

	writel(0, ap->regs + A_SG_CONTROL);
	setup_ring_params(ap, sge->cmdQ[0].dma_addr, sge->cmdQ[0].size,
			  A_SG_CMD0BASELWR, A_SG_CMD0BASEUPR, A_SG_CMD0SIZE);
	setup_ring_params(ap, sge->cmdQ[1].dma_addr, sge->cmdQ[1].size,
			  A_SG_CMD1BASELWR, A_SG_CMD1BASEUPR, A_SG_CMD1SIZE);
	setup_ring_params(ap, sge->freelQ[0].dma_addr,
			  sge->freelQ[0].size, A_SG_FL0BASELWR,
			  A_SG_FL0BASEUPR, A_SG_FL0SIZE);
	setup_ring_params(ap, sge->freelQ[1].dma_addr,
			  sge->freelQ[1].size, A_SG_FL1BASELWR,
			  A_SG_FL1BASEUPR, A_SG_FL1SIZE);

	/* The threshold comparison uses <. */
	writel(SGE_RX_SM_BUF_SIZE + 1, ap->regs + A_SG_FLTHRESHOLD);

	setup_ring_params(ap, sge->respQ.dma_addr, sge->respQ.size,
			  A_SG_RSPBASELWR, A_SG_RSPBASEUPR, A_SG_RSPSIZE);
	writel((u32)sge->respQ.size - 1, ap->regs + A_SG_RSPQUEUECREDIT);

	sge->sge_control = F_CMDQ0_ENABLE | F_CMDQ1_ENABLE | F_FL0_ENABLE |
		F_FL1_ENABLE | F_CPL_ENABLE | F_RESPONSE_QUEUE_ENABLE |
		V_CMDQ_PRIORITY(2) | F_DISABLE_CMDQ1_GTS | F_ISCSI_COALESCE |
		V_RX_PKT_OFFSET(sge->rx_pkt_pad);

#if defined(__BIG_ENDIAN_BITFIELD)
	sge->sge_control |= F_ENABLE_BIG_ENDIAN;
#endif

	/* Initialize no-resource timer */
	sge->intrtimer_nres = SGE_INTRTIMER_NRES * core_ticks_per_usec(ap);

	t1_sge_set_coalesce_params(sge, p);
}