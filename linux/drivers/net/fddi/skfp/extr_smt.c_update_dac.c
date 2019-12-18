#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* m; } ;
struct s_smc {TYPE_2__ mib; } ;
struct TYPE_3__ {int fddiMACUNDA_Flag; int fddiMACDA_Flag; int fddiMACDuplicateAddressCond; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_MAC ; 
 size_t MAC0 ; 
 int /*<<< orphan*/  SMT_COND_MAC_DUP_ADDR ; 
 int /*<<< orphan*/  smt_srf_event (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void update_dac(struct s_smc *smc, int report)
{
	int	cond ;

	cond = ( smc->mib.m[MAC0].fddiMACUNDA_Flag |
		smc->mib.m[MAC0].fddiMACDA_Flag) != 0 ;
	if (report && (cond != smc->mib.m[MAC0].fddiMACDuplicateAddressCond))
		smt_srf_event(smc, SMT_COND_MAC_DUP_ADDR,INDEX_MAC,cond) ;
	else
		smc->mib.m[MAC0].fddiMACDuplicateAddressCond = cond ;
}