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
 int SGDMA_STSREG_BUSY ; 
 int csrrd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgdma_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status ; 

__attribute__((used)) static int sgdma_rxbusy(struct altera_tse_private *priv)
{
	return csrrd32(priv->rx_dma_csr, sgdma_csroffs(status))
		       & SGDMA_STSREG_BUSY;
}