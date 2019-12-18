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
struct anybuss_host {int softint_pending; int /*<<< orphan*/  regmap; int /*<<< orphan*/  ind_ab; int /*<<< orphan*/  power_on; } ;

/* Variables and functions */
 unsigned int IND_AX_EVNT ; 
 int /*<<< orphan*/  REG_IND_AP ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  write_ind_ap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void softint_ack(struct anybuss_host *cd)
{
	unsigned int ind_ap;

	cd->softint_pending = false;
	if (!cd->power_on)
		return;
	regmap_read(cd->regmap, REG_IND_AP, &ind_ap);
	ind_ap &= ~IND_AX_EVNT;
	ind_ap |= atomic_read(&cd->ind_ab) & IND_AX_EVNT;
	write_ind_ap(cd->regmap, ind_ap);
}