#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rockchip_pcie {int /*<<< orphan*/  dev; scalar_t__ apb_base; scalar_t__ msg_region; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ PCIE_CLIENT_DEBUG_OUT_0 ; 
 int /*<<< orphan*/  PCIE_LINK_IS_L2 (int /*<<< orphan*/ ) ; 
 scalar_t__ PCIE_RC_SEND_PME_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jiffies_to_usecs (int) ; 
 int readl_poll_timeout (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int rockchip_pcie_wait_l2(struct rockchip_pcie *rockchip)
{
	u32 value;
	int err;

	/* send PME_TURN_OFF message */
	writel(0x0, rockchip->msg_region + PCIE_RC_SEND_PME_OFF);

	/* read LTSSM and wait for falling into L2 link state */
	err = readl_poll_timeout(rockchip->apb_base + PCIE_CLIENT_DEBUG_OUT_0,
				 value, PCIE_LINK_IS_L2(value), 20,
				 jiffies_to_usecs(5 * HZ));
	if (err) {
		dev_err(rockchip->dev, "PCIe link enter L2 timeout!\n");
		return err;
	}

	return 0;
}