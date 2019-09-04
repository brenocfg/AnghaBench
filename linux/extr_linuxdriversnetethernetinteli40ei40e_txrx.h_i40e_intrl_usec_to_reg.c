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
typedef  int u16 ;

/* Variables and functions */
 int INTRL_ENA ; 

__attribute__((used)) static inline u16 i40e_intrl_usec_to_reg(int intrl)
{
	if (intrl >> 2)
		return ((intrl >> 2) | INTRL_ENA);
	else
		return 0;
}