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
typedef  enum mdp4_cursor_format { ____Placeholder_mdp4_cursor_format } mdp4_cursor_format ;

/* Variables and functions */
 int MDP4_DMA_CURSOR_BLEND_CONFIG_FORMAT__MASK ; 
 int MDP4_DMA_CURSOR_BLEND_CONFIG_FORMAT__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP4_DMA_CURSOR_BLEND_CONFIG_FORMAT(enum mdp4_cursor_format val)
{
	return ((val) << MDP4_DMA_CURSOR_BLEND_CONFIG_FORMAT__SHIFT) & MDP4_DMA_CURSOR_BLEND_CONFIG_FORMAT__MASK;
}