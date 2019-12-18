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
typedef  int u32 ;
struct rvt_swqe {int psn; } ;
struct rvt_sge_state {int dummy; } ;

/* Variables and functions */
 int QIB_PSN_MASK ; 
 int rvt_restart_sge (struct rvt_sge_state*,struct rvt_swqe*,int) ; 

__attribute__((used)) static u32 restart_sge(struct rvt_sge_state *ss, struct rvt_swqe *wqe,
		       u32 psn, u32 pmtu)
{
	u32 len;

	len = ((psn - wqe->psn) & QIB_PSN_MASK) * pmtu;
	return rvt_restart_sge(ss, wqe, len);
}