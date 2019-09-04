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
struct sn_irq_info {int /*<<< orphan*/  irq_cookie; int /*<<< orphan*/  irq_irq; } ;
struct ia64_sal_retval {scalar_t__ v0; scalar_t__ status; } ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SAL_INTR_FREE ; 
 int /*<<< orphan*/  SN_SAL_IOIF_INTERRUPT ; 
 int /*<<< orphan*/  ia64_sal_oemcall_nolock (struct ia64_sal_retval*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tiocx_intr_free(nasid_t nasid, int widget,
				   struct sn_irq_info *sn_irq_info)
{
	struct ia64_sal_retval rv;
	rv.status = 0;
	rv.v0 = 0;

	ia64_sal_oemcall_nolock(&rv, SN_SAL_IOIF_INTERRUPT,
				SAL_INTR_FREE, nasid,
				widget, sn_irq_info->irq_irq,
				sn_irq_info->irq_cookie, 0, 0);
}