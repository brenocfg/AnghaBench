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
typedef  int u32 ;
struct ethtool_eee {int advertised; int supported; scalar_t__ eee_enabled; } ;
struct bnxt_link_info {int autoneg; int /*<<< orphan*/  advertising; } ;
struct bnxt {int flags; struct bnxt_link_info link_info; struct ethtool_eee eee; } ;

/* Variables and functions */
 int BNXT_AUTONEG_SPEED ; 
 int BNXT_FLAG_EEE_CAP ; 
 int _bnxt_fw_to_ethtool_adv_spds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bnxt_eee_config_ok(struct bnxt *bp)
{
	struct ethtool_eee *eee = &bp->eee;
	struct bnxt_link_info *link_info = &bp->link_info;

	if (!(bp->flags & BNXT_FLAG_EEE_CAP))
		return true;

	if (eee->eee_enabled) {
		u32 advertising =
			_bnxt_fw_to_ethtool_adv_spds(link_info->advertising, 0);

		if (!(link_info->autoneg & BNXT_AUTONEG_SPEED)) {
			eee->eee_enabled = 0;
			return false;
		}
		if (eee->advertised & ~advertising) {
			eee->advertised = advertising & eee->supported;
			return false;
		}
	}
	return true;
}