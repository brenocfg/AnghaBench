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
typedef  int u32 ;
struct altera_tse_private {int /*<<< orphan*/  tx_dma_desc; } ;

/* Variables and functions */
 int SGDMA_CONTROL_HW_OWNED ; 
 int /*<<< orphan*/  control ; 
 int csrrd8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dequeue_tx (struct altera_tse_private*) ; 
 int /*<<< orphan*/  sgdma_descroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgdma_txbusy (struct altera_tse_private*) ; 

u32 sgdma_tx_completions(struct altera_tse_private *priv)
{
	u32 ready = 0;

	if (!sgdma_txbusy(priv) &&
	    ((csrrd8(priv->tx_dma_desc, sgdma_descroffs(control))
	     & SGDMA_CONTROL_HW_OWNED) == 0) &&
	    (dequeue_tx(priv))) {
		ready = 1;
	}

	return ready;
}