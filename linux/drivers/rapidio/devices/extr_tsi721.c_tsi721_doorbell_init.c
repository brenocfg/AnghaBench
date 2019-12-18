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
typedef  int u64 ;
struct tsi721_device {scalar_t__ regs; scalar_t__ idb_dma; int /*<<< orphan*/  idb_base; TYPE_1__* pdev; int /*<<< orphan*/  idb_work; scalar_t__ db_discard_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBELL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IDB_QSIZE ; 
 int /*<<< orphan*/  IDB_QUEUE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TSI721_IDB_ENTRY_SIZE ; 
 scalar_t__ TSI721_IDQ_BASEL (int /*<<< orphan*/ ) ; 
 int TSI721_IDQ_BASEL_ADDR ; 
 scalar_t__ TSI721_IDQ_BASEU (int /*<<< orphan*/ ) ; 
 scalar_t__ TSI721_IDQ_CTL (int /*<<< orphan*/ ) ; 
 int TSI721_IDQ_INIT ; 
 scalar_t__ TSI721_IDQ_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ TSI721_IDQ_RP (int /*<<< orphan*/ ) ; 
 scalar_t__ TSI721_IDQ_SIZE (int /*<<< orphan*/ ) ; 
 int TSI721_IDQ_SIZE_VAL (int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  tsi721_db_dpc ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int tsi721_doorbell_init(struct tsi721_device *priv)
{
	/* Outbound Doorbells do not require any setup.
	 * Tsi721 uses dedicated PCI BAR1 to generate doorbells.
	 * That BAR1 was mapped during the probe routine.
	 */

	/* Initialize Inbound Doorbell processing DPC and queue */
	priv->db_discard_count = 0;
	INIT_WORK(&priv->idb_work, tsi721_db_dpc);

	/* Allocate buffer for inbound doorbells queue */
	priv->idb_base = dma_alloc_coherent(&priv->pdev->dev,
					    IDB_QSIZE * TSI721_IDB_ENTRY_SIZE,
					    &priv->idb_dma, GFP_KERNEL);
	if (!priv->idb_base)
		return -ENOMEM;

	tsi_debug(DBELL, &priv->pdev->dev,
		  "Allocated IDB buffer @ %p (phys = %pad)",
		  priv->idb_base, &priv->idb_dma);

	iowrite32(TSI721_IDQ_SIZE_VAL(IDB_QSIZE),
		priv->regs + TSI721_IDQ_SIZE(IDB_QUEUE));
	iowrite32(((u64)priv->idb_dma >> 32),
		priv->regs + TSI721_IDQ_BASEU(IDB_QUEUE));
	iowrite32(((u64)priv->idb_dma & TSI721_IDQ_BASEL_ADDR),
		priv->regs + TSI721_IDQ_BASEL(IDB_QUEUE));
	/* Enable accepting all inbound doorbells */
	iowrite32(0, priv->regs + TSI721_IDQ_MASK(IDB_QUEUE));

	iowrite32(TSI721_IDQ_INIT, priv->regs + TSI721_IDQ_CTL(IDB_QUEUE));

	iowrite32(0, priv->regs + TSI721_IDQ_RP(IDB_QUEUE));

	return 0;
}