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
struct asd_sas_phy {int /*<<< orphan*/  event_nr; } ;
struct asd_sas_event {struct asd_sas_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct asd_sas_event*) ; 
 int /*<<< orphan*/  sas_event_cache ; 

void sas_free_event(struct asd_sas_event *event)
{
	struct asd_sas_phy *phy = event->phy;

	kmem_cache_free(sas_event_cache, event);
	atomic_dec(&phy->event_nr);
}