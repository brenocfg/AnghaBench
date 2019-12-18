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
 int /*<<< orphan*/  SGDMA_CTRLREG_CLRINT ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  sgdma_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tse_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sgdma_clear_rxirq(struct altera_tse_private *priv)
{
	tse_set_bit(priv->rx_dma_csr, sgdma_csroffs(control),
		    SGDMA_CTRLREG_CLRINT);
}