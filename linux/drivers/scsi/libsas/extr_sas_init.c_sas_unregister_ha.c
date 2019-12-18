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
struct sas_ha_struct {int /*<<< orphan*/  event_q; int /*<<< orphan*/  disco_q; int /*<<< orphan*/  drain_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sas_drain_work (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_disable_events (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  sas_unregister_ports (struct sas_ha_struct*) ; 

int sas_unregister_ha(struct sas_ha_struct *sas_ha)
{
	sas_disable_events(sas_ha);
	sas_unregister_ports(sas_ha);

	/* flush unregistration work */
	mutex_lock(&sas_ha->drain_mutex);
	__sas_drain_work(sas_ha);
	mutex_unlock(&sas_ha->drain_mutex);

	destroy_workqueue(sas_ha->disco_q);
	destroy_workqueue(sas_ha->event_q);

	return 0;
}