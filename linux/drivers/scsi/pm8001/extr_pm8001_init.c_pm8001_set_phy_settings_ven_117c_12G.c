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
typedef  int /*<<< orphan*/  u32 ;
struct pm8001_mpi3_phy_pg_trx_config {int dummy; } ;
struct pm8001_hba_info {TYPE_1__* chip; } ;
typedef  int /*<<< orphan*/  phycfg_int ;
typedef  int /*<<< orphan*/  phycfg_ext ;
struct TYPE_2__ {int n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pm8001_mpi3_phy_pg_trx_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm8001_get_external_phy_settings (struct pm8001_hba_info*,struct pm8001_mpi3_phy_pg_trx_config*) ; 
 int /*<<< orphan*/  pm8001_get_internal_phy_settings (struct pm8001_hba_info*,struct pm8001_mpi3_phy_pg_trx_config*) ; 
 int /*<<< orphan*/  pm8001_get_phy_mask (struct pm8001_hba_info*,int*) ; 
 int /*<<< orphan*/  pm8001_set_phy_profile_single (struct pm8001_hba_info*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int pm8001_set_phy_settings_ven_117c_12G(struct pm8001_hba_info *pm8001_ha)
{
	struct pm8001_mpi3_phy_pg_trx_config phycfg_int;
	struct pm8001_mpi3_phy_pg_trx_config phycfg_ext;
	int phymask = 0;
	int i = 0;

	memset(&phycfg_int, 0, sizeof(phycfg_int));
	memset(&phycfg_ext, 0, sizeof(phycfg_ext));

	pm8001_get_internal_phy_settings(pm8001_ha, &phycfg_int);
	pm8001_get_external_phy_settings(pm8001_ha, &phycfg_ext);
	pm8001_get_phy_mask(pm8001_ha, &phymask);

	for (i = 0; i < pm8001_ha->chip->n_phy; i++) {
		if (phymask & (1 << i)) {/* Internal PHY */
			pm8001_set_phy_profile_single(pm8001_ha, i,
					sizeof(phycfg_int) / sizeof(u32),
					(u32 *)&phycfg_int);

		} else { /* External PHY */
			pm8001_set_phy_profile_single(pm8001_ha, i,
					sizeof(phycfg_ext) / sizeof(u32),
					(u32 *)&phycfg_ext);
		}
	}

	return 0;
}