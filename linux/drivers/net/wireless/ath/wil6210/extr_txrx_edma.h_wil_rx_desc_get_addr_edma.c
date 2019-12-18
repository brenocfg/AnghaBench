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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  addr_high; int /*<<< orphan*/  addr_low; } ;
struct wil_ring_rx_enhanced_dma {int /*<<< orphan*/  addr_high_high; TYPE_1__ addr; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
dma_addr_t wil_rx_desc_get_addr_edma(struct wil_ring_rx_enhanced_dma *dma)
{
	return le32_to_cpu(dma->addr.addr_low) |
			   ((u64)le16_to_cpu(dma->addr.addr_high) << 32) |
			   ((u64)le16_to_cpu(dma->addr_high_high) << 48);
}