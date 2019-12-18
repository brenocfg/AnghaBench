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
struct xlgmac_dma_desc {int /*<<< orphan*/  desc3; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_NORMAL_DESC3_CTXT_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_CTXT_POS ; 
 int XLGMAC_GET_REG_BITS_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlgmac_is_context_desc(struct xlgmac_dma_desc *dma_desc)
{
	/* Rx and Tx share CTXT bit, so check TDES3.CTXT bit */
	return XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				TX_NORMAL_DESC3_CTXT_POS,
				TX_NORMAL_DESC3_CTXT_LEN);
}