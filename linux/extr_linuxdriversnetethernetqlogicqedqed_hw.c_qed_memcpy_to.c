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
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned long) ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int /*<<< orphan*/  qed_memcpy_hw (struct qed_hwfn*,struct qed_ptt*,void*,int /*<<< orphan*/ ,size_t,int) ; 

void qed_memcpy_to(struct qed_hwfn *p_hwfn,
		   struct qed_ptt *p_ptt, u32 hw_addr, void *src, size_t n)
{
	DP_VERBOSE(p_hwfn, NETIF_MSG_HW,
		   "hw_addr 0x%x, hw_addr 0x%x, src %p size %lu\n",
		   hw_addr, hw_addr, src, (unsigned long)n);

	qed_memcpy_hw(p_hwfn, p_ptt, src, hw_addr, n, true);
}