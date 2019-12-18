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
struct TYPE_2__ {scalar_t__ fddiSMTCF_State; } ;
struct s_smc {TYPE_1__ mib; } ;

/* Variables and functions */
 int PA ; 
 int PB ; 
 scalar_t__ SC10_C_WRAP_B ; 
 scalar_t__ SC4_THRU_A ; 

int cfm_get_mac_output(struct s_smc *smc)
{
	return (smc->mib.fddiSMTCF_State == SC10_C_WRAP_B ||
		smc->mib.fddiSMTCF_State == SC4_THRU_A) ? PB : PA;
}