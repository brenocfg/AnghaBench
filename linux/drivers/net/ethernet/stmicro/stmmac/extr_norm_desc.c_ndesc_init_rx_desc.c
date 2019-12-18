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
struct dma_desc {int /*<<< orphan*/  des1; int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 scalar_t__ BUF_SIZE_2KiB ; 
 int RDES0_OWN ; 
 int RDES1_BUFFER1_SIZE_MASK ; 
 int RDES1_DISABLE_IC ; 
 int STMMAC_CHAIN_MODE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  ndesc_rx_set_on_chain (struct dma_desc*,int) ; 
 int /*<<< orphan*/  ndesc_rx_set_on_ring (struct dma_desc*,int,int) ; 

__attribute__((used)) static void ndesc_init_rx_desc(struct dma_desc *p, int disable_rx_ic, int mode,
			       int end, int bfsize)
{
	int bfsize1;

	p->des0 |= cpu_to_le32(RDES0_OWN);

	bfsize1 = min(bfsize, BUF_SIZE_2KiB - 1);
	p->des1 |= cpu_to_le32(bfsize1 & RDES1_BUFFER1_SIZE_MASK);

	if (mode == STMMAC_CHAIN_MODE)
		ndesc_rx_set_on_chain(p, end);
	else
		ndesc_rx_set_on_ring(p, end, bfsize);

	if (disable_rx_ic)
		p->des1 |= cpu_to_le32(RDES1_DISABLE_IC);
}