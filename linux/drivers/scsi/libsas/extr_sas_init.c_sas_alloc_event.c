#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sas_internal {TYPE_3__* dft; } ;
struct TYPE_5__ {TYPE_1__* shost; } ;
struct sas_ha_struct {scalar_t__ event_thres; TYPE_2__ core; } ;
struct asd_sas_phy {int /*<<< orphan*/  event_nr; int /*<<< orphan*/  id; int /*<<< orphan*/  in_shutdown; struct sas_ha_struct* ha; } ;
struct asd_sas_event {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {scalar_t__ lldd_control_phy; } ;
struct TYPE_4__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PHYE_SHUTDOWN ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct asd_sas_event*) ; 
 struct asd_sas_event* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_event_cache ; 
 int /*<<< orphan*/  sas_notify_phy_event (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

struct asd_sas_event *sas_alloc_event(struct asd_sas_phy *phy)
{
	struct asd_sas_event *event;
	gfp_t flags = in_interrupt() ? GFP_ATOMIC : GFP_KERNEL;
	struct sas_ha_struct *sas_ha = phy->ha;
	struct sas_internal *i =
		to_sas_internal(sas_ha->core.shost->transportt);

	event = kmem_cache_zalloc(sas_event_cache, flags);
	if (!event)
		return NULL;

	atomic_inc(&phy->event_nr);

	if (atomic_read(&phy->event_nr) > phy->ha->event_thres) {
		if (i->dft->lldd_control_phy) {
			if (cmpxchg(&phy->in_shutdown, 0, 1) == 0) {
				pr_notice("The phy%d bursting events, shut it down.\n",
					  phy->id);
				sas_notify_phy_event(phy, PHYE_SHUTDOWN);
			}
		} else {
			/* Do not support PHY control, stop allocating events */
			WARN_ONCE(1, "PHY control not supported.\n");
			kmem_cache_free(sas_event_cache, event);
			atomic_dec(&phy->event_nr);
			event = NULL;
		}
	}

	return event;
}