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
typedef  enum a6xx_state_block { ____Placeholder_a6xx_state_block } a6xx_state_block ;

/* Variables and functions */
 int CP_LOAD_STATE6_0_STATE_BLOCK__MASK ; 
 int CP_LOAD_STATE6_0_STATE_BLOCK__SHIFT ; 

__attribute__((used)) static inline uint32_t CP_LOAD_STATE6_0_STATE_BLOCK(enum a6xx_state_block val)
{
	return ((val) << CP_LOAD_STATE6_0_STATE_BLOCK__SHIFT) & CP_LOAD_STATE6_0_STATE_BLOCK__MASK;
}