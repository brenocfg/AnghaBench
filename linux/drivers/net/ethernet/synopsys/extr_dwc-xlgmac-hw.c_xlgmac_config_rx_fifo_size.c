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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_fifo_size; } ;
struct xlgmac_pdata {unsigned int rx_q_count; int /*<<< orphan*/  netdev; TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTL_Q_RQOMR ; 
 int /*<<< orphan*/  MTL_Q_RQOMR_RQS_LEN ; 
 int /*<<< orphan*/  MTL_Q_RQOMR_RQS_POS ; 
 int /*<<< orphan*/  XLGMAC_MTL_REG (struct xlgmac_pdata*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_info (struct xlgmac_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int xlgmac_calculate_per_queue_fifo (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void xlgmac_config_rx_fifo_size(struct xlgmac_pdata *pdata)
{
	unsigned int fifo_size;
	unsigned int i;
	u32 regval;

	fifo_size = xlgmac_calculate_per_queue_fifo(
					pdata->hw_feat.rx_fifo_size,
					pdata->rx_q_count);

	for (i = 0; i < pdata->rx_q_count; i++) {
		regval = readl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQOMR_RQS_POS,
					     MTL_Q_RQOMR_RQS_LEN, fifo_size);
		writel(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
	}

	netif_info(pdata, drv, pdata->netdev,
		   "%d Rx hardware queues, %d byte fifo per queue\n",
		   pdata->rx_q_count, ((fifo_size + 1) * 256));
}