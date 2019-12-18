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
struct sdio_func {int dummy; } ;
struct rsi_hw {TYPE_1__* priv; struct rsi_91x_sdiodev* rsi_dev; } ;
struct rsi_91x_sdiodev {struct sdio_func* pfunction; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int NUM_SOFT_QUEUES ; 
 int /*<<< orphan*/  rsi_hal_device_init (struct rsi_hw*) ; 
 int /*<<< orphan*/  rsi_handle_interrupt ; 
 int /*<<< orphan*/  rsi_init_sdio_slave_regs (struct rsi_hw*) ; 
 int /*<<< orphan*/  rsi_reset_card (struct sdio_func*) ; 
 int /*<<< orphan*/  rsi_setupcard (struct rsi_hw*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_claim_irq (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_enable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsi_sdio_reinit_device(struct rsi_hw *adapter)
{
	struct rsi_91x_sdiodev *sdev = adapter->rsi_dev;
	struct sdio_func *pfunction = sdev->pfunction;
	int ii;

	for (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_purge(&adapter->priv->tx_queue[ii]);

	/* Initialize device again */
	sdio_claim_host(pfunction);

	sdio_release_irq(pfunction);
	rsi_reset_card(pfunction);

	sdio_enable_func(pfunction);
	rsi_setupcard(adapter);
	rsi_init_sdio_slave_regs(adapter);
	sdio_claim_irq(pfunction, rsi_handle_interrupt);
	rsi_hal_device_init(adapter);

	sdio_release_host(pfunction);

	return 0;
}