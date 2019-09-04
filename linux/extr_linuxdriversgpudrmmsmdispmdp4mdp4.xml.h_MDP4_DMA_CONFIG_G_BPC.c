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
typedef  enum mdp_bpc { ____Placeholder_mdp_bpc } mdp_bpc ;

/* Variables and functions */
 int MDP4_DMA_CONFIG_G_BPC__MASK ; 
 int MDP4_DMA_CONFIG_G_BPC__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP4_DMA_CONFIG_G_BPC(enum mdp_bpc val)
{
	return ((val) << MDP4_DMA_CONFIG_G_BPC__SHIFT) & MDP4_DMA_CONFIG_G_BPC__MASK;
}