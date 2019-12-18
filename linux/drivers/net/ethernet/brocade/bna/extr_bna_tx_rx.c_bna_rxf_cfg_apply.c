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
 scalar_t__ bna_rxf_allmulti_cfg_apply (struct bna_rxf*) ; 
 scalar_t__ bna_rxf_mcast_cfg_apply (struct bna_rxf*) ; 
 scalar_t__ bna_rxf_promisc_cfg_apply (struct bna_rxf*) ; 
 scalar_t__ bna_rxf_rss_cfg_apply (struct bna_rxf*) ; 
 scalar_t__ bna_rxf_ucast_cfg_apply (struct bna_rxf*) ; 
 scalar_t__ bna_rxf_vlan_cfg_apply (struct bna_rxf*) ; 
 scalar_t__ bna_rxf_vlan_strip_cfg_apply (struct bna_rxf*) ; 

__attribute__((used)) static int
bna_rxf_cfg_apply(struct bna_rxf *rxf)
{
	if (bna_rxf_ucast_cfg_apply(rxf))
		return 1;

	if (bna_rxf_mcast_cfg_apply(rxf))
		return 1;

	if (bna_rxf_promisc_cfg_apply(rxf))
		return 1;

	if (bna_rxf_allmulti_cfg_apply(rxf))
		return 1;

	if (bna_rxf_vlan_cfg_apply(rxf))
		return 1;

	if (bna_rxf_vlan_strip_cfg_apply(rxf))
		return 1;

	if (bna_rxf_rss_cfg_apply(rxf))
		return 1;

	return 0;
}