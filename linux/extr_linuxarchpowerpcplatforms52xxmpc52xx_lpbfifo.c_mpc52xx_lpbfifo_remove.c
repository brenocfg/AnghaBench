#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * regs; int /*<<< orphan*/  irq; int /*<<< orphan*/  bcom_rx_task; int /*<<< orphan*/  bcom_tx_task; } ;

/* Variables and functions */
 int LPBFIFO_REG_ENABLE ; 
 int /*<<< orphan*/  bcom_gen_bd_rx_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_gen_bd_tx_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_get_task_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 TYPE_1__ lpbfifo ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mpc52xx_lpbfifo_remove(struct platform_device *op)
{
	if (lpbfifo.dev != &op->dev)
		return 0;

	/* Put FIFO in reset */
	out_be32(lpbfifo.regs + LPBFIFO_REG_ENABLE, 0x01010000);

	/* Release the bestcomm transmit task */
	free_irq(bcom_get_task_irq(lpbfifo.bcom_tx_task), &lpbfifo);
	bcom_gen_bd_tx_release(lpbfifo.bcom_tx_task);
	
	/* Release the bestcomm receive task */
	free_irq(bcom_get_task_irq(lpbfifo.bcom_rx_task), &lpbfifo);
	bcom_gen_bd_rx_release(lpbfifo.bcom_rx_task);

	free_irq(lpbfifo.irq, &lpbfifo);
	iounmap(lpbfifo.regs);
	lpbfifo.regs = NULL;
	lpbfifo.dev = NULL;

	return 0;
}