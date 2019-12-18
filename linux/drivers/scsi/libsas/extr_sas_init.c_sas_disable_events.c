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
struct sas_ha_struct {int /*<<< orphan*/  drain_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_HA_REGISTERED ; 
 int /*<<< orphan*/  __sas_drain_work (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sas_disable_events(struct sas_ha_struct *sas_ha)
{
	/* Set the state to unregistered to avoid further unchained
	 * events to be queued, and flush any in-progress drainers
	 */
	mutex_lock(&sas_ha->drain_mutex);
	spin_lock_irq(&sas_ha->lock);
	clear_bit(SAS_HA_REGISTERED, &sas_ha->state);
	spin_unlock_irq(&sas_ha->lock);
	__sas_drain_work(sas_ha);
	mutex_unlock(&sas_ha->drain_mutex);
}