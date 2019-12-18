#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  active; } ;
struct pvc_device {TYPE_2__ state; TYPE_4__* frad; int /*<<< orphan*/  open_count; } ;
struct net_device {struct pvc_device* ml_priv; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_9__ {int flags; } ;
struct TYPE_6__ {scalar_t__ lmi; } ;
struct TYPE_8__ {int dce_changed; TYPE_1__ settings; } ;

/* Variables and functions */
 int EIO ; 
 int IFF_UP ; 
 scalar_t__ LMI_NONE ; 
 int /*<<< orphan*/ * dev_to_hdlc (TYPE_4__*) ; 
 int /*<<< orphan*/  netif_carrier_ok (TYPE_4__*) ; 
 int /*<<< orphan*/  pvc_carrier (int /*<<< orphan*/ ,struct pvc_device*) ; 
 TYPE_3__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvc_open(struct net_device *dev)
{
	struct pvc_device *pvc = dev->ml_priv;

	if ((pvc->frad->flags & IFF_UP) == 0)
		return -EIO;  /* Frad must be UP in order to activate PVC */

	if (pvc->open_count++ == 0) {
		hdlc_device *hdlc = dev_to_hdlc(pvc->frad);
		if (state(hdlc)->settings.lmi == LMI_NONE)
			pvc->state.active = netif_carrier_ok(pvc->frad);

		pvc_carrier(pvc->state.active, pvc);
		state(hdlc)->dce_changed = 1;
	}
	return 0;
}