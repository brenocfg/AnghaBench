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
struct wil6210_priv {scalar_t__ use_enhanced_dma_hw; } ;

/* Variables and functions */

__attribute__((used)) static inline int wil_get_min_tx_ring_id(struct wil6210_priv *wil)
{
	/* In Enhanced DMA ring 0 is reserved for RX */
	return wil->use_enhanced_dma_hw ? 1 : 0;
}