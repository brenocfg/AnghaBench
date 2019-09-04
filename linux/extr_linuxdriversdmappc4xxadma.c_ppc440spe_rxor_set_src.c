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
typedef  size_t u8 ;
struct xor_cb {TYPE_1__* ops; } ;
struct ppc440spe_adma_desc_slot {struct xor_cb* hw_desc; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  l; int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CUED_XOR_BASE ; 

__attribute__((used)) static void ppc440spe_rxor_set_src(struct ppc440spe_adma_desc_slot *desc,
	u8 xor_arg_no, dma_addr_t addr)
{
	struct xor_cb *xcb = desc->hw_desc;

	xcb->ops[xor_arg_no].h |= DMA_CUED_XOR_BASE;
	xcb->ops[xor_arg_no].l = addr;
}