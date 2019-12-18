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
typedef  int uint32_t ;
typedef  enum mdp4_dma { ____Placeholder_mdp4_dma } mdp4_dma ;

/* Variables and functions */
 int __offset_DMA (int) ; 

__attribute__((used)) static inline uint32_t REG_MDP4_DMA_CSC_PRE_LV_VAL(enum mdp4_dma i0, uint32_t i1) { return 0x00003600 + __offset_DMA(i0) + 0x4*i1; }