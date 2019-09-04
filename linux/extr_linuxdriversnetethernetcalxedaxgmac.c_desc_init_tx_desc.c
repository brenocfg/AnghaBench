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
struct xgmac_dma_desc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXDESC_END_RING ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xgmac_dma_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void desc_init_tx_desc(struct xgmac_dma_desc *p, u32 ring_size)
{
	memset(p, 0, sizeof(*p) * ring_size);
	p[ring_size - 1].flags = cpu_to_le32(TXDESC_END_RING);
}