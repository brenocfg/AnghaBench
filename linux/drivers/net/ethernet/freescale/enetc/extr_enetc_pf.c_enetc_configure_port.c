#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct enetc_pf {int /*<<< orphan*/  vlan_promisc_simap; TYPE_1__* si; } ;
struct enetc_hw {int dummy; } ;
struct TYPE_4__ {struct enetc_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_PMR ; 
 int /*<<< orphan*/  ENETC_PMR_EN ; 
 int /*<<< orphan*/  ENETC_PSIPMR ; 
 int ENETC_RSSHASH_KEY_SIZE ; 
 int /*<<< orphan*/  ENETC_VLAN_PROMISC_MAP_ALL ; 
 int /*<<< orphan*/  enetc_configure_port_mac (struct enetc_hw*) ; 
 int /*<<< orphan*/  enetc_configure_port_pmac (struct enetc_hw*) ; 
 int /*<<< orphan*/  enetc_port_assign_rfs_entries (TYPE_1__*) ; 
 int /*<<< orphan*/  enetc_port_setup_primary_mac_address (TYPE_1__*) ; 
 int /*<<< orphan*/  enetc_port_si_configure (TYPE_1__*) ; 
 int /*<<< orphan*/  enetc_port_wr (struct enetc_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_set_rss_key (struct enetc_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enetc_set_vlan_promisc (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void enetc_configure_port(struct enetc_pf *pf)
{
	u8 hash_key[ENETC_RSSHASH_KEY_SIZE];
	struct enetc_hw *hw = &pf->si->hw;

	enetc_configure_port_pmac(hw);

	enetc_configure_port_mac(hw);

	enetc_port_si_configure(pf->si);

	/* set up hash key */
	get_random_bytes(hash_key, ENETC_RSSHASH_KEY_SIZE);
	enetc_set_rss_key(hw, hash_key);

	/* split up RFS entries */
	enetc_port_assign_rfs_entries(pf->si);

	/* fix-up primary MAC addresses, if not set already */
	enetc_port_setup_primary_mac_address(pf->si);

	/* enforce VLAN promisc mode for all SIs */
	pf->vlan_promisc_simap = ENETC_VLAN_PROMISC_MAP_ALL;
	enetc_set_vlan_promisc(hw, pf->vlan_promisc_simap);

	enetc_port_wr(hw, ENETC_PSIPMR, 0);

	/* enable port */
	enetc_port_wr(hw, ENETC_PMR, ENETC_PMR_EN);
}