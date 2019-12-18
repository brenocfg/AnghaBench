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
struct TYPE_2__ {int /*<<< orphan*/  ioc_fwstate; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int bfa_ioc_cb_join_pos (struct bfa_ioc_s*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_cb_sync_leave(struct bfa_ioc_s *ioc)
{
	u32 r32 = readl(ioc->ioc_regs.ioc_fwstate);
	u32 join_pos = bfa_ioc_cb_join_pos(ioc);

	writel((r32 & ~join_pos), ioc->ioc_regs.ioc_fwstate);
}