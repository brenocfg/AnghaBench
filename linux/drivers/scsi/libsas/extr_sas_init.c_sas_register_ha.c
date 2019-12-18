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
struct sas_ha_struct {void* event_q; int /*<<< orphan*/  eh_ata_q; int /*<<< orphan*/  eh_done_q; void* disco_q; int /*<<< orphan*/  dev; int /*<<< orphan*/  event_thres; int /*<<< orphan*/  eh_dev_q; int /*<<< orphan*/  defer_q; int /*<<< orphan*/  eh_wait_q; int /*<<< orphan*/  drain_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  hashed_sas_addr; int /*<<< orphan*/  phy_port_lock; int /*<<< orphan*/  disco_mutex; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SAS_HA_REGISTERED ; 
 int /*<<< orphan*/  SAS_PHY_SHUTDOWN_THRES ; 
 void* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 int /*<<< orphan*/  sas_hash_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sas_init_events (struct sas_ha_struct*) ; 
 int sas_register_phys (struct sas_ha_struct*) ; 
 int sas_register_ports (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  sas_unregister_ports (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int sas_register_ha(struct sas_ha_struct *sas_ha)
{
	char name[64];
	int error = 0;

	mutex_init(&sas_ha->disco_mutex);
	spin_lock_init(&sas_ha->phy_port_lock);
	sas_hash_addr(sas_ha->hashed_sas_addr, sas_ha->sas_addr);

	set_bit(SAS_HA_REGISTERED, &sas_ha->state);
	spin_lock_init(&sas_ha->lock);
	mutex_init(&sas_ha->drain_mutex);
	init_waitqueue_head(&sas_ha->eh_wait_q);
	INIT_LIST_HEAD(&sas_ha->defer_q);
	INIT_LIST_HEAD(&sas_ha->eh_dev_q);

	sas_ha->event_thres = SAS_PHY_SHUTDOWN_THRES;

	error = sas_register_phys(sas_ha);
	if (error) {
		pr_notice("couldn't register sas phys:%d\n", error);
		return error;
	}

	error = sas_register_ports(sas_ha);
	if (error) {
		pr_notice("couldn't register sas ports:%d\n", error);
		goto Undo_phys;
	}

	error = sas_init_events(sas_ha);
	if (error) {
		pr_notice("couldn't start event thread:%d\n", error);
		goto Undo_ports;
	}

	error = -ENOMEM;
	snprintf(name, sizeof(name), "%s_event_q", dev_name(sas_ha->dev));
	sas_ha->event_q = create_singlethread_workqueue(name);
	if (!sas_ha->event_q)
		goto Undo_ports;

	snprintf(name, sizeof(name), "%s_disco_q", dev_name(sas_ha->dev));
	sas_ha->disco_q = create_singlethread_workqueue(name);
	if (!sas_ha->disco_q)
		goto Undo_event_q;

	INIT_LIST_HEAD(&sas_ha->eh_done_q);
	INIT_LIST_HEAD(&sas_ha->eh_ata_q);

	return 0;

Undo_event_q:
	destroy_workqueue(sas_ha->event_q);
Undo_ports:
	sas_unregister_ports(sas_ha);
Undo_phys:

	return error;
}