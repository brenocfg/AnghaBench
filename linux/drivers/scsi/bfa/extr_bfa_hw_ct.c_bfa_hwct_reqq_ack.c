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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * cpe_q_ctrl; } ;
struct TYPE_4__ {TYPE_1__ bfa_regs; } ;
struct bfa_s {TYPE_2__ iocfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_hwct_reqq_ack(struct bfa_s *bfa, int reqq)
{
	u32	r32;

	r32 = readl(bfa->iocfc.bfa_regs.cpe_q_ctrl[reqq]);
	writel(r32, bfa->iocfc.bfa_regs.cpe_q_ctrl[reqq]);
}