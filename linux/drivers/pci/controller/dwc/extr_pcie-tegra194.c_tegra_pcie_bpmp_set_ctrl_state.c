#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tegra_pcie_dw {int cid; int /*<<< orphan*/  bpmp; } ;
struct TYPE_6__ {int size; struct tegra_bpmp_message* data; } ;
struct TYPE_5__ {int size; struct tegra_bpmp_message* data; } ;
struct TYPE_4__ {int pcie_controller; int enable; } ;
struct tegra_bpmp_message {TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ controller_state; int /*<<< orphan*/  cmd; } ;
struct mrq_uphy_response {TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ controller_state; int /*<<< orphan*/  cmd; } ;
struct mrq_uphy_request {TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; TYPE_1__ controller_state; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_UPHY_PCIE_CONTROLLER_STATE ; 
 int /*<<< orphan*/  MRQ_UPHY ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_transfer (int /*<<< orphan*/ ,struct tegra_bpmp_message*) ; 

__attribute__((used)) static int tegra_pcie_bpmp_set_ctrl_state(struct tegra_pcie_dw *pcie,
					  bool enable)
{
	struct mrq_uphy_response resp;
	struct tegra_bpmp_message msg;
	struct mrq_uphy_request req;

	/* Controller-5 doesn't need to have its state set by BPMP-FW */
	if (pcie->cid == 5)
		return 0;

	memset(&req, 0, sizeof(req));
	memset(&resp, 0, sizeof(resp));

	req.cmd = CMD_UPHY_PCIE_CONTROLLER_STATE;
	req.controller_state.pcie_controller = pcie->cid;
	req.controller_state.enable = enable;

	memset(&msg, 0, sizeof(msg));
	msg.mrq = MRQ_UPHY;
	msg.tx.data = &req;
	msg.tx.size = sizeof(req);
	msg.rx.data = &resp;
	msg.rx.size = sizeof(resp);

	return tegra_bpmp_transfer(pcie->bpmp, &msg);
}