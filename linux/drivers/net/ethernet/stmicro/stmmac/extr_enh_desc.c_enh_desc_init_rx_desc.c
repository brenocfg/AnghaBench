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
 int /*<<< orphan*/  BUF_SIZE_8KiB ; 
 int ERDES1_BUFFER1_SIZE_MASK ; 
 int ERDES1_DISABLE_IC ; 
 int RDES0_OWN ; 
 int STMMAC_CHAIN_MODE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ehn_desc_rx_set_on_chain (struct dma_desc*) ; 
 int /*<<< orphan*/  ehn_desc_rx_set_on_ring (struct dma_desc*,int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enh_desc_init_rx_desc(struct dma_desc *p, int disable_rx_ic,
				  int mode, int end, int bfsize)
{
	int bfsize1;

	p->des0 |= cpu_to_le32(RDES0_OWN);

	bfsize1 = min(bfsize, BUF_SIZE_8KiB);
	p->des1 |= cpu_to_le32(bfsize1 & ERDES1_BUFFER1_SIZE_MASK);

	if (mode == STMMAC_CHAIN_MODE)
		ehn_desc_rx_set_on_chain(p);
	else
		ehn_desc_rx_set_on_ring(p, end, bfsize);

	if (disable_rx_ic)
		p->des1 |= cpu_to_le32(ERDES1_DISABLE_IC);
}