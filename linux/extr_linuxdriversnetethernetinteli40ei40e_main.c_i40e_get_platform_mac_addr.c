#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct i40e_pf {TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ eth_platform_get_mac_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_get_mac_addr (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_get_platform_mac_addr(struct pci_dev *pdev, struct i40e_pf *pf)
{
	if (eth_platform_get_mac_address(&pdev->dev, pf->hw.mac.addr))
		i40e_get_mac_addr(&pf->hw, pf->hw.mac.addr);
}