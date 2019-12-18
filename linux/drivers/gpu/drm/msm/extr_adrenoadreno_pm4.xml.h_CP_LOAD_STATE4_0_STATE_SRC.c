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
typedef  enum a4xx_state_src { ____Placeholder_a4xx_state_src } a4xx_state_src ;

/* Variables and functions */
 int CP_LOAD_STATE4_0_STATE_SRC__MASK ; 
 int CP_LOAD_STATE4_0_STATE_SRC__SHIFT ; 

__attribute__((used)) static inline uint32_t CP_LOAD_STATE4_0_STATE_SRC(enum a4xx_state_src val)
{
	return ((val) << CP_LOAD_STATE4_0_STATE_SRC__SHIFT) & CP_LOAD_STATE4_0_STATE_SRC__MASK;
}