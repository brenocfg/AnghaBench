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
struct xen_drm_front_info {int num_evt_pairs; int /*<<< orphan*/  io_lock; TYPE_3__* evt_pairs; } ;
typedef  enum xen_drm_front_evtchnl_state { ____Placeholder_xen_drm_front_evtchnl_state } xen_drm_front_evtchnl_state ;
struct TYPE_4__ {int state; } ;
struct TYPE_5__ {int state; } ;
struct TYPE_6__ {TYPE_1__ evt; TYPE_2__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void xen_drm_front_evtchnl_set_state(struct xen_drm_front_info *front_info,
				     enum xen_drm_front_evtchnl_state state)
{
	unsigned long flags;
	int i;

	if (!front_info->evt_pairs)
		return;

	spin_lock_irqsave(&front_info->io_lock, flags);
	for (i = 0; i < front_info->num_evt_pairs; i++) {
		front_info->evt_pairs[i].req.state = state;
		front_info->evt_pairs[i].evt.state = state;
	}
	spin_unlock_irqrestore(&front_info->io_lock, flags);
}