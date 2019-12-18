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
typedef  enum mdp5_intf_type { ____Placeholder_mdp5_intf_type } mdp5_intf_type ;

/* Variables and functions */
 int MDP5_DISP_INTF_SEL_INTF2__MASK ; 
 int MDP5_DISP_INTF_SEL_INTF2__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP5_DISP_INTF_SEL_INTF2(enum mdp5_intf_type val)
{
	return ((val) << MDP5_DISP_INTF_SEL_INTF2__SHIFT) & MDP5_DISP_INTF_SEL_INTF2__MASK;
}