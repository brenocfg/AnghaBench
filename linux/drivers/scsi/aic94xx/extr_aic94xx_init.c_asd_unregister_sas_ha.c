#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  shost; } ;
struct TYPE_4__ {int /*<<< orphan*/  sas_port; int /*<<< orphan*/  sas_phy; TYPE_1__ core; } ;
struct asd_ha_struct {TYPE_2__ sas_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_remove_host (int /*<<< orphan*/ ) ; 
 int sas_unregister_ha (TYPE_2__*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_unregister_sas_ha(struct asd_ha_struct *asd_ha)
{
	int err;

	err = sas_unregister_ha(&asd_ha->sas_ha);

	sas_remove_host(asd_ha->sas_ha.core.shost);
	scsi_host_put(asd_ha->sas_ha.core.shost);

	kfree(asd_ha->sas_ha.sas_phy);
	kfree(asd_ha->sas_ha.sas_port);

	return err;
}