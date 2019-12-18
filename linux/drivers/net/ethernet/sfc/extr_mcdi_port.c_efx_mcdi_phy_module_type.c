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
typedef  scalar_t__ u32 ;
struct efx_nic {struct efx_mcdi_phy_data* phy_data; } ;
struct efx_mcdi_phy_data {scalar_t__ media; } ;

/* Variables and functions */
 scalar_t__ MC_CMD_MEDIA_QSFP_PLUS ; 
 scalar_t__ MC_CMD_MEDIA_SFP_PLUS ; 
 int efx_mcdi_phy_get_module_eeprom_byte (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 efx_mcdi_phy_module_type(struct efx_nic *efx)
{
	struct efx_mcdi_phy_data *phy_data = efx->phy_data;

	if (phy_data->media != MC_CMD_MEDIA_QSFP_PLUS)
		return phy_data->media;

	/* A QSFP+ NIC may actually have an SFP+ module attached.
	 * The ID is page 0, byte 0.
	 */
	switch (efx_mcdi_phy_get_module_eeprom_byte(efx, 0, 0)) {
	case 0x3:
		return MC_CMD_MEDIA_SFP_PLUS;
	case 0xc:
	case 0xd:
		return MC_CMD_MEDIA_QSFP_PLUS;
	default:
		return 0;
	}
}