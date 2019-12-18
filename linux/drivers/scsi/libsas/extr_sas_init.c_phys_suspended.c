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
struct sas_ha_struct {int num_phys; struct asd_sas_phy** sas_phy; } ;
struct asd_sas_phy {scalar_t__ suspended; } ;

/* Variables and functions */

__attribute__((used)) static int phys_suspended(struct sas_ha_struct *ha)
{
	int i, rc = 0;

	for (i = 0; i < ha->num_phys; i++) {
		struct asd_sas_phy *phy = ha->sas_phy[i];

		if (phy->suspended)
			rc++;
	}

	return rc;
}