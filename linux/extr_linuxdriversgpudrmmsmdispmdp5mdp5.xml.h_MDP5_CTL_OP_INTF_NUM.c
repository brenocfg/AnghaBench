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
typedef  enum mdp5_intfnum { ____Placeholder_mdp5_intfnum } mdp5_intfnum ;

/* Variables and functions */
 int MDP5_CTL_OP_INTF_NUM__MASK ; 
 int MDP5_CTL_OP_INTF_NUM__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP5_CTL_OP_INTF_NUM(enum mdp5_intfnum val)
{
	return ((val) << MDP5_CTL_OP_INTF_NUM__SHIFT) & MDP5_CTL_OP_INTF_NUM__MASK;
}