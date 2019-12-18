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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_6__ {TYPE_4__* mu; TYPE_1__* regs; } ;
struct TYPE_7__ {TYPE_2__ mv; } ;
struct hptiop_hba {TYPE_3__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  outbound_msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  outbound_doorbell; } ;

/* Variables and functions */
 int MVIOP_MU_OUTBOUND_INT_MSG ; 
 int MVIOP_MU_OUTBOUND_INT_POSTQUEUE ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  hptiop_message_callback (struct hptiop_hba*,int) ; 
 int /*<<< orphan*/  hptiop_request_callback_mv (struct hptiop_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_outbound_read (TYPE_4__*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iop_intr_mv(struct hptiop_hba *hba)
{
	u32 status;
	int ret = 0;

	status = readl(&hba->u.mv.regs->outbound_doorbell);
	writel(~status, &hba->u.mv.regs->outbound_doorbell);

	if (status & MVIOP_MU_OUTBOUND_INT_MSG) {
		u32 msg;
		msg = readl(&hba->u.mv.mu->outbound_msg);
		dprintk("received outbound msg %x\n", msg);
		hptiop_message_callback(hba, msg);
		ret = 1;
	}

	if (status & MVIOP_MU_OUTBOUND_INT_POSTQUEUE) {
		u64 tag;

		while ((tag = mv_outbound_read(hba->u.mv.mu)))
			hptiop_request_callback_mv(hba, tag);
		ret = 1;
	}

	return ret;
}