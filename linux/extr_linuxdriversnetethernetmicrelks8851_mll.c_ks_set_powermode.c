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
struct ks_net {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_GRR ; 
 int /*<<< orphan*/  KS_PMECR ; 
 unsigned int PMECR_PM_MASK ; 
 int /*<<< orphan*/  hw ; 
 unsigned int ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  netif_dbg (struct ks_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void ks_set_powermode(struct ks_net *ks, unsigned pwrmode)
{
	unsigned pmecr;

	netif_dbg(ks, hw, ks->netdev, "setting power mode %d\n", pwrmode);

	ks_rdreg16(ks, KS_GRR);
	pmecr = ks_rdreg16(ks, KS_PMECR);
	pmecr &= ~PMECR_PM_MASK;
	pmecr |= pwrmode;

	ks_wrreg16(ks, KS_PMECR, pmecr);
}