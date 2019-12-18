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
struct xen_drm_front_info {int num_evt_pairs; TYPE_1__* evt_pairs; } ;
struct TYPE_2__ {int /*<<< orphan*/  evt; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  evtchnl_free (struct xen_drm_front_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void xen_drm_front_evtchnl_free_all(struct xen_drm_front_info *front_info)
{
	int i;

	if (!front_info->evt_pairs)
		return;

	for (i = 0; i < front_info->num_evt_pairs; i++) {
		evtchnl_free(front_info, &front_info->evt_pairs[i].req);
		evtchnl_free(front_info, &front_info->evt_pairs[i].evt);
	}

	kfree(front_info->evt_pairs);
	front_info->evt_pairs = NULL;
}