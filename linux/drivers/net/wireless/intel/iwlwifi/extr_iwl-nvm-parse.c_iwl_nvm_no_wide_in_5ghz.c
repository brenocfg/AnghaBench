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
typedef  int u8 ;
typedef  int u16 ;
struct iwl_trans {int /*<<< orphan*/  dev; TYPE_1__* trans_cfg; } ;
struct iwl_cfg {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_EEPROM (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ IWL_DEVICE_FAMILY_7000 ; 
 int SUBSYSTEM_ID ; 
 int be16_to_cpup (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool
iwl_nvm_no_wide_in_5ghz(struct iwl_trans *trans, const struct iwl_cfg *cfg,
			const __be16 *nvm_hw)
{
	/*
	 * Workaround a bug in Indonesia SKUs where the regulatory in
	 * some 7000-family OTPs erroneously allow wide channels in
	 * 5GHz.  To check for Indonesia, we take the SKU value from
	 * bits 1-4 in the subsystem ID and check if it is either 5 or
	 * 9.  In those cases, we need to force-disable wide channels
	 * in 5GHz otherwise the FW will throw a sysassert when we try
	 * to use them.
	 */
	if (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_7000) {
		/*
		 * Unlike the other sections in the NVM, the hw
		 * section uses big-endian.
		 */
		u16 subsystem_id = be16_to_cpup(nvm_hw + SUBSYSTEM_ID);
		u8 sku = (subsystem_id & 0x1e) >> 1;

		if (sku == 5 || sku == 9) {
			IWL_DEBUG_EEPROM(trans->dev,
					 "disabling wide channels in 5GHz (0x%0x %d)\n",
					 subsystem_id, sku);
			return true;
		}
	}

	return false;
}