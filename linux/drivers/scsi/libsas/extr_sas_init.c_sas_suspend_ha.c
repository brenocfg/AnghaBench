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
struct TYPE_2__ {int /*<<< orphan*/  shost; } ;
struct sas_ha_struct {int num_phys; int /*<<< orphan*/  drain_mutex; struct asd_sas_port** sas_port; TYPE_1__ core; } ;
struct asd_sas_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_SUSPEND ; 
 int /*<<< orphan*/  __sas_drain_work (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_disable_events (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  sas_discover_event (struct asd_sas_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 

void sas_suspend_ha(struct sas_ha_struct *ha)
{
	int i;

	sas_disable_events(ha);
	scsi_block_requests(ha->core.shost);
	for (i = 0; i < ha->num_phys; i++) {
		struct asd_sas_port *port = ha->sas_port[i];

		sas_discover_event(port, DISCE_SUSPEND);
	}

	/* flush suspend events while unregistered */
	mutex_lock(&ha->drain_mutex);
	__sas_drain_work(ha);
	mutex_unlock(&ha->drain_mutex);
}