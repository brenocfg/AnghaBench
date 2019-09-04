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
struct altera_tse_private {int /*<<< orphan*/  tx_dma_csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGDMA_CSR_CTL_GLOBAL_INTR ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  msgdma_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tse_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void msgdma_enable_txirq(struct altera_tse_private *priv)
{
	tse_set_bit(priv->tx_dma_csr, msgdma_csroffs(control),
		    MSGDMA_CSR_CTL_GLOBAL_INTR);
}