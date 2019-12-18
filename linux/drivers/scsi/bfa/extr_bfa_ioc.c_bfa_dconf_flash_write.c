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
struct bfa_dconf_s {int dummy; } ;
struct bfa_dconf_mod_s {int /*<<< orphan*/  bfa; int /*<<< orphan*/  dconf; int /*<<< orphan*/  instance; } ;
typedef  scalar_t__ bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FLASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BFA_FLASH_PART_DRV ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  bfa_dconf_cbfn ; 
 scalar_t__ bfa_flash_update_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_dconf_mod_s*) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bfa_status_t
bfa_dconf_flash_write(struct bfa_dconf_mod_s *dconf)
{
	bfa_status_t bfa_status;
	bfa_trc(dconf->bfa, 0);

	bfa_status = bfa_flash_update_part(BFA_FLASH(dconf->bfa),
				BFA_FLASH_PART_DRV, dconf->instance,
				dconf->dconf,  sizeof(struct bfa_dconf_s), 0,
				bfa_dconf_cbfn, dconf);
	if (bfa_status != BFA_STATUS_OK)
		WARN_ON(bfa_status);
	bfa_trc(dconf->bfa, bfa_status);

	return bfa_status;
}