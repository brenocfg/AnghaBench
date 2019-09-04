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
struct xgmac_dma_desc {int /*<<< orphan*/  buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXDESC1_END_RING ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_set_buf_len (struct xgmac_dma_desc*,int) ; 
 int /*<<< orphan*/  memset (struct xgmac_dma_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void desc_init_rx_desc(struct xgmac_dma_desc *p, int ring_size,
				     int buf_sz)
{
	struct xgmac_dma_desc *end = p + ring_size - 1;

	memset(p, 0, sizeof(*p) * ring_size);

	for (; p <= end; p++)
		desc_set_buf_len(p, buf_sz);

	end->buf_size |= cpu_to_le32(RXDESC1_END_RING);
}