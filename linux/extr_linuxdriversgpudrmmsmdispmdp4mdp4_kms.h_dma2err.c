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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum mdp4_dma { ____Placeholder_mdp4_dma } mdp4_dma ;

/* Variables and functions */
#define  DMA_E 130 
#define  DMA_P 129 
#define  DMA_S 128 
 int /*<<< orphan*/  MDP4_IRQ_EXTERNAL_INTF_UDERRUN ; 
 int /*<<< orphan*/  MDP4_IRQ_PRIMARY_INTF_UDERRUN ; 

__attribute__((used)) static inline uint32_t dma2err(enum mdp4_dma dma)
{
	switch (dma) {
	case DMA_P:    return MDP4_IRQ_PRIMARY_INTF_UDERRUN;
	case DMA_S:    return 0;  // ???
	case DMA_E:    return MDP4_IRQ_EXTERNAL_INTF_UDERRUN;
	default:       return 0;
	}
}