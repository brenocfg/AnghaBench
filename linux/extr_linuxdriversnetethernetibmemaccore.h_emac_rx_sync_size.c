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

/* Variables and functions */
 int EMAC_DMA_ALIGN (scalar_t__) ; 
 scalar_t__ emac_rx_size (int) ; 

__attribute__((used)) static inline int emac_rx_sync_size(int mtu)
{
	return EMAC_DMA_ALIGN(emac_rx_size(mtu) + 2);
}