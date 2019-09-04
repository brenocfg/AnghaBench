#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_5__ {int dma_irqs_enabled; int /*<<< orphan*/ * regs; int /*<<< orphan*/  bcom_rx_task; TYPE_4__* dev; int /*<<< orphan*/  bcom_tx_task; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; scalar_t__ regs_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCOM_INITIATOR_SCLPC ; 
 int /*<<< orphan*/  BCOM_IPR_SCLPC ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int LPBFIFO_REG_ENABLE ; 
 scalar_t__ LPBFIFO_REG_FIFO_DATA ; 
 int /*<<< orphan*/  bcom_gen_bd_rx_init (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcom_gen_bd_rx_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_gen_bd_tx_init (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_get_task_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ lpbfifo ; 
 int /*<<< orphan*/  mpc52xx_lpbfifo_bcom_irq ; 
 int /*<<< orphan*/  mpc52xx_lpbfifo_irq ; 
 scalar_t__ of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/ * of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpc52xx_lpbfifo_probe(struct platform_device *op)
{
	struct resource res;
	int rc = -ENOMEM;

	if (lpbfifo.dev != NULL)
		return -ENOSPC;

	lpbfifo.irq = irq_of_parse_and_map(op->dev.of_node, 0);
	if (!lpbfifo.irq)
		return -ENODEV;

	if (of_address_to_resource(op->dev.of_node, 0, &res))
		return -ENODEV;
	lpbfifo.regs_phys = res.start;
	lpbfifo.regs = of_iomap(op->dev.of_node, 0);
	if (!lpbfifo.regs)
		return -ENOMEM;

	spin_lock_init(&lpbfifo.lock);

	/* Put FIFO into reset */
	out_be32(lpbfifo.regs + LPBFIFO_REG_ENABLE, 0x01010000);

	/* Register the interrupt handler */
	rc = request_irq(lpbfifo.irq, mpc52xx_lpbfifo_irq, 0,
			 "mpc52xx-lpbfifo", &lpbfifo);
	if (rc)
		goto err_irq;

	/* Request the Bestcomm receive (fifo --> memory) task and IRQ */
	lpbfifo.bcom_rx_task =
		bcom_gen_bd_rx_init(2, res.start + LPBFIFO_REG_FIFO_DATA,
				    BCOM_INITIATOR_SCLPC, BCOM_IPR_SCLPC,
				    16*1024*1024);
	if (!lpbfifo.bcom_rx_task)
		goto err_bcom_rx;

	rc = request_irq(bcom_get_task_irq(lpbfifo.bcom_rx_task),
			 mpc52xx_lpbfifo_bcom_irq, 0,
			 "mpc52xx-lpbfifo-rx", &lpbfifo);
	if (rc)
		goto err_bcom_rx_irq;

	lpbfifo.dma_irqs_enabled = 1;

	/* Request the Bestcomm transmit (memory --> fifo) task and IRQ */
	lpbfifo.bcom_tx_task =
		bcom_gen_bd_tx_init(2, res.start + LPBFIFO_REG_FIFO_DATA,
				    BCOM_INITIATOR_SCLPC, BCOM_IPR_SCLPC);
	if (!lpbfifo.bcom_tx_task)
		goto err_bcom_tx;

	lpbfifo.dev = &op->dev;
	return 0;

 err_bcom_tx:
	free_irq(bcom_get_task_irq(lpbfifo.bcom_rx_task), &lpbfifo);
 err_bcom_rx_irq:
	bcom_gen_bd_rx_release(lpbfifo.bcom_rx_task);
 err_bcom_rx:
 err_irq:
	iounmap(lpbfifo.regs);
	lpbfifo.regs = NULL;

	dev_err(&op->dev, "mpc52xx_lpbfifo_probe() failed\n");
	return -ENODEV;
}