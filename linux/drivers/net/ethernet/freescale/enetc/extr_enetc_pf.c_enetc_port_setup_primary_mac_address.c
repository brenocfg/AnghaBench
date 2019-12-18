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
struct enetc_hw {int dummy; } ;
struct enetc_si {TYPE_1__* pdev; struct enetc_hw hw; } ;
struct enetc_pf {int total_vfs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_ADDR_LEN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  enetc_pf_get_primary_mac_addr (struct enetc_hw*,int,unsigned char*) ; 
 int /*<<< orphan*/  enetc_pf_set_primary_mac_addr (struct enetc_hw*,int,unsigned char*) ; 
 struct enetc_pf* enetc_si_priv (struct enetc_si*) ; 
 int /*<<< orphan*/  eth_random_addr (unsigned char*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (unsigned char*) ; 

__attribute__((used)) static void enetc_port_setup_primary_mac_address(struct enetc_si *si)
{
	unsigned char mac_addr[MAX_ADDR_LEN];
	struct enetc_pf *pf = enetc_si_priv(si);
	struct enetc_hw *hw = &si->hw;
	int i;

	/* check MAC addresses for PF and all VFs, if any is 0 set it ro rand */
	for (i = 0; i < pf->total_vfs + 1; i++) {
		enetc_pf_get_primary_mac_addr(hw, i, mac_addr);
		if (!is_zero_ether_addr(mac_addr))
			continue;
		eth_random_addr(mac_addr);
		dev_info(&si->pdev->dev, "no MAC address specified for SI%d, using %pM\n",
			 i, mac_addr);
		enetc_pf_set_primary_mac_addr(hw, i, mac_addr);
	}
}