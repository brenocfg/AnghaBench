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
 scalar_t__ ETH_FCS_LEN ; 
 int RXDESC_FRAME_LEN_MASK ; 
 int RXDESC_FRAME_LEN_OFFSET ; 
 int RXDESC_FRAME_TYPE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int desc_get_rx_frame_len(struct xgmac_dma_desc *p)
{
	u32 data = le32_to_cpu(p->flags);
	u32 len = (data & RXDESC_FRAME_LEN_MASK) >> RXDESC_FRAME_LEN_OFFSET;
	if (data & RXDESC_FRAME_TYPE)
		len -= ETH_FCS_LEN;

	return len;
}