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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ hfn_mbox_cmd; scalar_t__ hfn_mbox; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int BFI_IOC_MSGLEN_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,int) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void
bfa_ioc_mbox_send(struct bfa_ioc_s *ioc, void *ioc_msg, int len)
{
	u32 *msgp = (u32 *) ioc_msg;
	u32 i;

	bfa_trc(ioc, msgp[0]);
	bfa_trc(ioc, len);

	WARN_ON(len > BFI_IOC_MSGLEN_MAX);

	/*
	 * first write msg to mailbox registers
	 */
	for (i = 0; i < len / sizeof(u32); i++)
		writel(cpu_to_le32(msgp[i]),
			ioc->ioc_regs.hfn_mbox + i * sizeof(u32));

	for (; i < BFI_IOC_MSGLEN_MAX / sizeof(u32); i++)
		writel(0, ioc->ioc_regs.hfn_mbox + i * sizeof(u32));

	/*
	 * write 1 to mailbox CMD to trigger LPU event
	 */
	writel(1, ioc->ioc_regs.hfn_mbox_cmd);
	(void) readl(ioc->ioc_regs.hfn_mbox_cmd);
}