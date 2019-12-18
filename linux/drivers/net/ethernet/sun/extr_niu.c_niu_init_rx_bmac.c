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
typedef  int u64 ;
struct niu_rdc_tables {int first_table_num; } ;
struct niu_parent {struct niu_rdc_tables* rdc_group_cfg; } ;
struct niu {size_t port; struct niu_parent* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAC_ADDR_CMPEN ; 
 int BMAC_ADDR_CMPEN_EN0 ; 
 int /*<<< orphan*/  BMAC_ADD_FILT0 ; 
 int /*<<< orphan*/  BMAC_ADD_FILT00_MASK ; 
 int /*<<< orphan*/  BMAC_ADD_FILT1 ; 
 int /*<<< orphan*/  BMAC_ADD_FILT12_MASK ; 
 int /*<<< orphan*/  BMAC_ADD_FILT2 ; 
 int /*<<< orphan*/  BMAC_HASH_TBL (unsigned long) ; 
 int /*<<< orphan*/  BRXMAC_CONFIG ; 
 int BRXMAC_CONFIG_ADDR_FILT_EN ; 
 int BRXMAC_CONFIG_DISCARD_DIS ; 
 int BRXMAC_CONFIG_ENABLE ; 
 int BRXMAC_CONFIG_HASH_FILT_EN ; 
 int BRXMAC_CONFIG_PROMISC ; 
 int BRXMAC_CONFIG_PROMISC_GRP ; 
 int BRXMAC_CONFIG_STRIP_FCS ; 
 int BRXMAC_CONFIG_STRIP_PAD ; 
 int /*<<< orphan*/  BRXMAC_STATUS_MASK ; 
 unsigned long MAC_NUM_HASH ; 
 int /*<<< orphan*/  niu_set_multicast_mac_rdc_table (struct niu*,int,int) ; 
 int /*<<< orphan*/  niu_set_primary_mac_rdc_table (struct niu*,int,int) ; 
 int nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_init_rx_bmac(struct niu *np)
{
	struct niu_parent *parent = np->parent;
	struct niu_rdc_tables *tp = &parent->rdc_group_cfg[np->port];
	int first_rdc_table = tp->first_table_num;
	unsigned long i;
	u64 val;

	nw64_mac(BMAC_ADD_FILT0, 0);
	nw64_mac(BMAC_ADD_FILT1, 0);
	nw64_mac(BMAC_ADD_FILT2, 0);
	nw64_mac(BMAC_ADD_FILT12_MASK, 0);
	nw64_mac(BMAC_ADD_FILT00_MASK, 0);
	for (i = 0; i < MAC_NUM_HASH; i++)
		nw64_mac(BMAC_HASH_TBL(i), 0);
	niu_set_primary_mac_rdc_table(np, first_rdc_table, 1);
	niu_set_multicast_mac_rdc_table(np, first_rdc_table, 1);
	nw64_mac(BRXMAC_STATUS_MASK, ~(u64)0);

	val = nr64_mac(BRXMAC_CONFIG);
	val &= ~(BRXMAC_CONFIG_ENABLE |
		 BRXMAC_CONFIG_STRIP_PAD |
		 BRXMAC_CONFIG_STRIP_FCS |
		 BRXMAC_CONFIG_PROMISC |
		 BRXMAC_CONFIG_PROMISC_GRP |
		 BRXMAC_CONFIG_ADDR_FILT_EN |
		 BRXMAC_CONFIG_DISCARD_DIS);
	val |= (BRXMAC_CONFIG_HASH_FILT_EN);
	nw64_mac(BRXMAC_CONFIG, val);

	val = nr64_mac(BMAC_ADDR_CMPEN);
	val |= BMAC_ADDR_CMPEN_EN0;
	nw64_mac(BMAC_ADDR_CMPEN, val);
}