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
struct nfp_abm {scalar_t__ eswitch_mode; } ;

/* Variables and functions */
 scalar_t__ DEVLINK_ESWITCH_MODE_LEGACY ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_eswitch_set_legacy (struct nfp_abm*) ; 

__attribute__((used)) static void nfp_abm_eswitch_clean_up(struct nfp_abm *abm)
{
	if (abm->eswitch_mode != DEVLINK_ESWITCH_MODE_LEGACY)
		WARN_ON(nfp_abm_eswitch_set_legacy(abm));
}