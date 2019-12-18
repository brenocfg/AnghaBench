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
struct bfa_s {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LPS_MAX_VPORTS_SUPP_CB ; 
 int /*<<< orphan*/  BFA_LPS_MAX_VPORTS_SUPP_CT ; 
 scalar_t__ BFA_PCI_DEVICE_ID_CT ; 
 scalar_t__ bfa_ioc_devid (int /*<<< orphan*/ *) ; 

u32
bfa_lps_get_max_vport(struct bfa_s *bfa)
{
	if (bfa_ioc_devid(&bfa->ioc) == BFA_PCI_DEVICE_ID_CT)
		return BFA_LPS_MAX_VPORTS_SUPP_CT;
	else
		return BFA_LPS_MAX_VPORTS_SUPP_CB;
}