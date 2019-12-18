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
struct TYPE_2__ {int /*<<< orphan*/  pdev; int /*<<< orphan*/  sysctl_bar; } ;
struct qtnf_pcie_topaz_state {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  QTN_EP_RESET_WAIT_MS ; 
 int /*<<< orphan*/  TOPAZ_IPC_IRQ_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPAZ_LH_IPC4_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOPAZ_RC_RST_EP_IRQ ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qtnf_topaz_reset_ep(struct qtnf_pcie_topaz_state *ts)
{
	writel(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_RST_EP_IRQ),
	       TOPAZ_LH_IPC4_INT(ts->base.sysctl_bar));
	msleep(QTN_EP_RESET_WAIT_MS);
	pci_restore_state(ts->base.pdev);
}