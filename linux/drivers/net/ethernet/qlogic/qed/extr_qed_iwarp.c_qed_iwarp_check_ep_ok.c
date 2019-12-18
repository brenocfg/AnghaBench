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
struct qed_iwarp_ep {scalar_t__ sig; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,struct qed_iwarp_ep*) ; 
 scalar_t__ QED_EP_SIG ; 

__attribute__((used)) static inline bool
qed_iwarp_check_ep_ok(struct qed_hwfn *p_hwfn, struct qed_iwarp_ep *ep)
{
	if (!ep || (ep->sig != QED_EP_SIG)) {
		DP_ERR(p_hwfn, "ERROR ON ASYNC ep=%p\n", ep);
		return false;
	}

	return true;
}