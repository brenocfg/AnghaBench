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
typedef  scalar_t__ u64 ;
struct ia64_sal_retval {scalar_t__ status; scalar_t__ v0; } ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SAL_INTR_ALLOC ; 
 int /*<<< orphan*/  SN_SAL_IOIF_INTERRUPT ; 
 int /*<<< orphan*/  ia64_sal_oemcall_nolock (struct ia64_sal_retval*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u64 tiocx_intr_alloc(nasid_t nasid, int widget,
					u64 sn_irq_info,
					int req_irq, nasid_t req_nasid,
					int req_slice)
{
	struct ia64_sal_retval rv;
	rv.status = 0;
	rv.v0 = 0;

	ia64_sal_oemcall_nolock(&rv, SN_SAL_IOIF_INTERRUPT,
				SAL_INTR_ALLOC, nasid,
				widget, sn_irq_info, req_irq,
				req_nasid, req_slice);
	return rv.status;
}