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
typedef  scalar_t__ u_short ;
struct s_p_tab {scalar_t__ p_num; } ;

/* Variables and functions */
 struct s_p_tab* p_tab ; 

__attribute__((used)) static const struct s_p_tab *smt_get_ptab(u_short para)
{
	const struct s_p_tab	*pt ;
	for (pt = p_tab ; pt->p_num && pt->p_num != para ; pt++)
		;
	return pt->p_num ? pt : NULL;
}