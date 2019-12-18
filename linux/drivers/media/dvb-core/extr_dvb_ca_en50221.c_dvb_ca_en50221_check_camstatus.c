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
struct dvb_ca_slot {scalar_t__ slot_state; int /*<<< orphan*/  camchange_count; int /*<<< orphan*/  camchange_type; } ;
struct dvb_ca_private {int flags; int /*<<< orphan*/  open; TYPE_1__* pub; struct dvb_ca_slot* slot_info; } ;
struct TYPE_2__ {int (* poll_slot_status ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_CA_EN50221_CAMCHANGE_INSERTED ; 
 int /*<<< orphan*/  DVB_CA_EN50221_CAMCHANGE_REMOVED ; 
 int DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE ; 
 int DVB_CA_EN50221_POLL_CAM_CHANGED ; 
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int DVB_CA_EN50221_POLL_CAM_READY ; 
 scalar_t__ DVB_CA_SLOTSTATE_NONE ; 
 scalar_t__ DVB_CA_SLOTSTATE_VALIDATE ; 
 scalar_t__ DVB_CA_SLOTSTATE_WAITREADY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int stub1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_ca_en50221_check_camstatus(struct dvb_ca_private *ca, int slot)
{
	struct dvb_ca_slot *sl = &ca->slot_info[slot];
	int slot_status;
	int cam_present_now;
	int cam_changed;

	/* IRQ mode */
	if (ca->flags & DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE)
		return (atomic_read(&sl->camchange_count) != 0);

	/* poll mode */
	slot_status = ca->pub->poll_slot_status(ca->pub, slot, ca->open);

	cam_present_now = (slot_status & DVB_CA_EN50221_POLL_CAM_PRESENT) ? 1 : 0;
	cam_changed = (slot_status & DVB_CA_EN50221_POLL_CAM_CHANGED) ? 1 : 0;
	if (!cam_changed) {
		int cam_present_old = (sl->slot_state != DVB_CA_SLOTSTATE_NONE);

		cam_changed = (cam_present_now != cam_present_old);
	}

	if (cam_changed) {
		if (!cam_present_now)
			sl->camchange_type = DVB_CA_EN50221_CAMCHANGE_REMOVED;
		else
			sl->camchange_type = DVB_CA_EN50221_CAMCHANGE_INSERTED;
		atomic_set(&sl->camchange_count, 1);
	} else {
		if ((sl->slot_state == DVB_CA_SLOTSTATE_WAITREADY) &&
		    (slot_status & DVB_CA_EN50221_POLL_CAM_READY)) {
			/* move to validate state if reset is completed */
			sl->slot_state = DVB_CA_SLOTSTATE_VALIDATE;
		}
	}

	return cam_changed;
}