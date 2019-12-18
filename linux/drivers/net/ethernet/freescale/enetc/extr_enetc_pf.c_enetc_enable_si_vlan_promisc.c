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
struct enetc_pf {int /*<<< orphan*/  vlan_promisc_simap; TYPE_1__* si; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  enetc_set_vlan_promisc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_enable_si_vlan_promisc(struct enetc_pf *pf, int si_idx)
{
	pf->vlan_promisc_simap |= BIT(si_idx);
	enetc_set_vlan_promisc(&pf->si->hw, pf->vlan_promisc_simap);
}