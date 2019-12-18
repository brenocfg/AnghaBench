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
typedef  size_t u8 ;
struct TYPE_2__ {int maxtcs; int* tcbwtable; int /*<<< orphan*/ * tsatable; } ;
struct ice_dcbx_cfg {TYPE_1__ etsrec; } ;
struct ice_port_info {struct ice_dcbx_cfg local_dcbx_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_IEEE_TSA_ETS ; 
 int /*<<< orphan*/  ICE_IEEE_TSA_STRICT ; 
 size_t ICE_MAX_TRAFFIC_CLASS ; 

__attribute__((used)) static void ice_cfg_etsrec_defaults(struct ice_port_info *pi)
{
	struct ice_dcbx_cfg *dcbcfg = &pi->local_dcbx_cfg;
	u8 i;

	/* Ensure ETS recommended DCB configuration is not already set */
	if (dcbcfg->etsrec.maxtcs)
		return;

	/* In CEE mode, set the default to 1 TC */
	dcbcfg->etsrec.maxtcs = 1;
	for (i = 0; i < ICE_MAX_TRAFFIC_CLASS; i++) {
		dcbcfg->etsrec.tcbwtable[i] = i ? 0 : 100;
		dcbcfg->etsrec.tsatable[i] = i ? ICE_IEEE_TSA_STRICT :
						 ICE_IEEE_TSA_ETS;
	}
}