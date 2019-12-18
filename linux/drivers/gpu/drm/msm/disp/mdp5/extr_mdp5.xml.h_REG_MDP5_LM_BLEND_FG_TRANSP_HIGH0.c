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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ __offset_BLEND (scalar_t__) ; 
 scalar_t__ __offset_LM (scalar_t__) ; 

__attribute__((used)) static inline uint32_t REG_MDP5_LM_BLEND_FG_TRANSP_HIGH0(uint32_t i0, uint32_t i1) { return 0x00000014 + __offset_LM(i0) + __offset_BLEND(i1); }