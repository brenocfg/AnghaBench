#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  intr_status; } ;
struct TYPE_4__ {TYPE_1__ bfa_regs; } ;
struct bfa_s {TYPE_2__ iocfc; int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int CPE_Q_NUM (int /*<<< orphan*/ ,int) ; 
 int __HFN_INT_CPE_Q0 ; 
 int /*<<< orphan*/  bfa_ioc_pcifn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_hwcb_reqq_ack_msix(struct bfa_s *bfa, int reqq)
{
	writel(__HFN_INT_CPE_Q0 << CPE_Q_NUM(bfa_ioc_pcifn(&bfa->ioc), reqq),
			bfa->iocfc.bfa_regs.intr_status);
}