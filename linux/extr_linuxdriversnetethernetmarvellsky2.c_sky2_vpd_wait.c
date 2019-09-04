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
typedef  int u16 ;
struct sky2_hw {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ PCI_VPD_ADDR ; 
 int PCI_VPD_ADDR_F ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int sky2_pci_read16 (struct sky2_hw const*,scalar_t__) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int sky2_vpd_wait(const struct sky2_hw *hw, int cap, u16 busy)
{
	unsigned long start = jiffies;

	while ( (sky2_pci_read16(hw, cap + PCI_VPD_ADDR) & PCI_VPD_ADDR_F) == busy) {
		/* Can take up to 10.6 ms for write */
		if (time_after(jiffies, start + HZ/4)) {
			dev_err(&hw->pdev->dev, "VPD cycle timed out\n");
			return -ETIMEDOUT;
		}
		msleep(1);
	}

	return 0;
}