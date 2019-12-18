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
struct sas_ha_struct {int num_phys; TYPE_1__** sas_phy; } ;
struct TYPE_2__ {scalar_t__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  sas_deform_port (TYPE_1__*,int /*<<< orphan*/ ) ; 

void sas_unregister_ports(struct sas_ha_struct *sas_ha)
{
	int i;

	for (i = 0; i < sas_ha->num_phys; i++)
		if (sas_ha->sas_phy[i]->port)
			sas_deform_port(sas_ha->sas_phy[i], 0);

}