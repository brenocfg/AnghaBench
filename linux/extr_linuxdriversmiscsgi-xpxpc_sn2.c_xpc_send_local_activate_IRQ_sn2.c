#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct amo {int /*<<< orphan*/  variable; } ;
struct TYPE_2__ {scalar_t__ amos_page_pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (int) ; 
 size_t BIT_WORD (int) ; 
 int /*<<< orphan*/  FETCHOP_OR ; 
 int /*<<< orphan*/  FETCHOP_STORE_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_AMO (int /*<<< orphan*/ ) ; 
 int XPC_ACTIVATE_IRQ_AMOS_SN2 ; 
 scalar_t__ __va (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpc_activate_IRQ_rcvd ; 
 int /*<<< orphan*/  xpc_activate_IRQ_rcvd_lock ; 
 int /*<<< orphan*/  xpc_activate_IRQ_wq ; 
 TYPE_1__* xpc_vars_sn2 ; 

__attribute__((used)) static void
xpc_send_local_activate_IRQ_sn2(int from_nasid)
{
	unsigned long irq_flags;
	struct amo *amos = (struct amo *)__va(xpc_vars_sn2->amos_page_pa +
					      (XPC_ACTIVATE_IRQ_AMOS_SN2 *
					      sizeof(struct amo)));

	/* fake the sending and receipt of an activate IRQ from remote nasid */
	FETCHOP_STORE_OP(TO_AMO((u64)&amos[BIT_WORD(from_nasid / 2)].variable),
			 FETCHOP_OR, BIT_MASK(from_nasid / 2));

	spin_lock_irqsave(&xpc_activate_IRQ_rcvd_lock, irq_flags);
	xpc_activate_IRQ_rcvd++;
	spin_unlock_irqrestore(&xpc_activate_IRQ_rcvd_lock, irq_flags);

	wake_up_interruptible(&xpc_activate_IRQ_wq);
}