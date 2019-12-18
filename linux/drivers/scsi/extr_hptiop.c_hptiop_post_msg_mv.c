#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {TYPE_2__* regs; TYPE_1__* mu; } ;
struct TYPE_8__ {TYPE_3__ mv; } ;
struct hptiop_hba {TYPE_4__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  inbound_doorbell; } ;
struct TYPE_5__ {int /*<<< orphan*/  inbound_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVIOP_MU_INBOUND_INT_MSG ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hptiop_post_msg_mv(struct hptiop_hba *hba, u32 msg)
{
	writel(msg, &hba->u.mv.mu->inbound_msg);
	writel(MVIOP_MU_INBOUND_INT_MSG, &hba->u.mv.regs->inbound_doorbell);
	readl(&hba->u.mv.regs->inbound_doorbell);
}