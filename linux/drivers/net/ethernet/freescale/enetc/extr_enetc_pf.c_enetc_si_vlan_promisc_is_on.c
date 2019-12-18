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
struct enetc_pf {int vlan_promisc_simap; } ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static bool enetc_si_vlan_promisc_is_on(struct enetc_pf *pf, int si_idx)
{
	return pf->vlan_promisc_simap & BIT(si_idx);
}