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
struct bna_rxf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_SOFT_CLEANUP ; 
 int /*<<< orphan*/  bna_rxf_allmulti_cfg_reset (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rxf_mcast_cfg_reset (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rxf_promisc_cfg_reset (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rxf_rss_cfg_soft_reset (struct bna_rxf*) ; 
 int /*<<< orphan*/  bna_rxf_ucast_cfg_reset (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rxf_vlan_cfg_soft_reset (struct bna_rxf*) ; 

__attribute__((used)) static void
bna_rxf_cfg_reset(struct bna_rxf *rxf)
{
	bna_rxf_ucast_cfg_reset(rxf, BNA_SOFT_CLEANUP);
	bna_rxf_mcast_cfg_reset(rxf, BNA_SOFT_CLEANUP);
	bna_rxf_promisc_cfg_reset(rxf, BNA_SOFT_CLEANUP);
	bna_rxf_allmulti_cfg_reset(rxf, BNA_SOFT_CLEANUP);
	bna_rxf_vlan_cfg_soft_reset(rxf);
	bna_rxf_rss_cfg_soft_reset(rxf);
}