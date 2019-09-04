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
typedef  enum board_idx { ____Placeholder_board_idx } board_idx ;

/* Variables and functions */
 int NETXTREME_C_VF ; 
 int NETXTREME_E_VF ; 
 int NETXTREME_S_VF ; 

__attribute__((used)) static bool bnxt_vf_pciid(enum board_idx idx)
{
	return (idx == NETXTREME_C_VF || idx == NETXTREME_E_VF ||
		idx == NETXTREME_S_VF);
}