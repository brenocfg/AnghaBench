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
struct dvb_ca_private {int flags; TYPE_1__* slot_info; TYPE_2__* pub; } ;
struct TYPE_4__ {int (* poll_slot_status ) (TYPE_2__*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  slot_state; } ;

/* Variables and functions */
 int DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE ; 
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int /*<<< orphan*/  DVB_CA_SLOTSTATE_NONE ; 
 int /*<<< orphan*/  dvb_ca_en50221_thread_update_delay (struct dvb_ca_private*) ; 
 int stub1 (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_ca_en50221_poll_cam_gone(struct dvb_ca_private *ca, int slot)
{
	int changed = 0;
	int status;

	/*
	 * we need this extra check for annoying interfaces like the
	 * budget-av
	 */
	if ((!(ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE)) &&
	    (ca->pub->poll_slot_status)) {
		status = ca->pub->poll_slot_status(ca->pub, slot, 0);
		if (!(status &
			DVB_CA_EN50221_POLL_CAM_PRESENT)) {
			ca->slot_info[slot].slot_state = DVB_CA_SLOTSTATE_NONE;
			dvb_ca_en50221_thread_update_delay(ca);
			changed = 1;
		}
	}
	return changed;
}