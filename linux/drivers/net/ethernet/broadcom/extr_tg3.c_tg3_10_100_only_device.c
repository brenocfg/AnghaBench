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
struct tg3 {int phy_flags; } ;
struct pci_device_id {int driver_data; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5703 ; 
 scalar_t__ ASIC_REV_5705 ; 
 int /*<<< orphan*/  GRC_MISC_CFG ; 
 int GRC_MISC_CFG_BOARD_ID_MASK ; 
 int TG3_DRV_DATA_FLAG_10_100_ONLY ; 
 int TG3_DRV_DATA_FLAG_5705_10_100 ; 
 int TG3_PHYFLG_IS_FET ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tg3_10_100_only_device(struct tg3 *tp,
				   const struct pci_device_id *ent)
{
	u32 grc_misc_cfg = tr32(GRC_MISC_CFG) & GRC_MISC_CFG_BOARD_ID_MASK;

	if ((tg3_asic_rev(tp) == ASIC_REV_5703 &&
	     (grc_misc_cfg == 0x8000 || grc_misc_cfg == 0x4000)) ||
	    (tp->phy_flags & TG3_PHYFLG_IS_FET))
		return true;

	if (ent->driver_data & TG3_DRV_DATA_FLAG_10_100_ONLY) {
		if (tg3_asic_rev(tp) == ASIC_REV_5705) {
			if (ent->driver_data & TG3_DRV_DATA_FLAG_5705_10_100)
				return true;
		} else {
			return true;
		}
	}

	return false;
}