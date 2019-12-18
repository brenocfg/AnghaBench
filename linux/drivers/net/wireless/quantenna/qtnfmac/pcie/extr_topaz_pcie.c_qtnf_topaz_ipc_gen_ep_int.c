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
struct TYPE_2__ {int /*<<< orphan*/  sysctl_bar; } ;
struct qtnf_pcie_topaz_state {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOPAZ_CTL_M2L_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPAZ_IPC_IRQ_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPAZ_RC_CTRL_IRQ ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qtnf_topaz_ipc_gen_ep_int(void *arg)
{
	struct qtnf_pcie_topaz_state *ts = arg;

	writel(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_CTRL_IRQ),
	       TOPAZ_CTL_M2L_INT(ts->base.sysctl_bar));
}