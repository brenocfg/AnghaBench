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
typedef  union bfi_ioc_i2h_msg_u {int dummy; } bfi_ioc_i2h_msg_u ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ lpu_mbox_cmd; scalar_t__ lpu_mbox; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int htonl (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static bool
bfa_ioc_msgget(struct bfa_ioc *ioc, void *mbmsg)
{
	u32	*msgp = mbmsg;
	u32	r32;
	int		i;

	r32 = readl(ioc->ioc_regs.lpu_mbox_cmd);
	if ((r32 & 1) == 0)
		return false;

	/**
	 * read the MBOX msg
	 */
	for (i = 0; i < (sizeof(union bfi_ioc_i2h_msg_u) / sizeof(u32));
	     i++) {
		r32 = readl(ioc->ioc_regs.lpu_mbox +
				   i * sizeof(u32));
		msgp[i] = htonl(r32);
	}

	/**
	 * turn off mailbox interrupt by clearing mailbox status
	 */
	writel(1, ioc->ioc_regs.lpu_mbox_cmd);
	readl(ioc->ioc_regs.lpu_mbox_cmd);

	return true;
}