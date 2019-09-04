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
struct ep93xx_dma_chan {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ M2P_STATUS ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline u32 m2p_channel_state(struct ep93xx_dma_chan *edmac)
{
	return (readl(edmac->regs + M2P_STATUS) >> 4) & 0x3;
}