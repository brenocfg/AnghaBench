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
struct altera_tse_private {int /*<<< orphan*/  rx_dma_csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGDMA_CSR_STAT_IRQ ; 
 int /*<<< orphan*/  csrwr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgdma_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status ; 

void msgdma_clear_rxirq(struct altera_tse_private *priv)
{
	csrwr32(MSGDMA_CSR_STAT_IRQ, priv->rx_dma_csr, msgdma_csroffs(status));
}