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
typedef  int u8 ;
struct mlxsw_swid_config {int /*<<< orphan*/  properties; scalar_t__ used_properties; int /*<<< orphan*/  type; scalar_t__ used_type; } ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_cmd_mbox_config_profile_swid_config_mask_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_config_profile_swid_config_properties_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_config_profile_swid_config_type_set (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_pci_config_profile_swid_config(struct mlxsw_pci *mlxsw_pci,
				     char *mbox, int index,
				     const struct mlxsw_swid_config *swid)
{
	u8 mask = 0;

	if (swid->used_type) {
		mlxsw_cmd_mbox_config_profile_swid_config_type_set(
			mbox, index, swid->type);
		mask |= 1;
	}
	if (swid->used_properties) {
		mlxsw_cmd_mbox_config_profile_swid_config_properties_set(
			mbox, index, swid->properties);
		mask |= 2;
	}
	mlxsw_cmd_mbox_config_profile_swid_config_mask_set(mbox, index, mask);
}