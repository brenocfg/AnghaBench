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
typedef  int uint ;
struct scsi_info {int flags; int state; int new_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  proc_work; int /*<<< orphan*/  work_q; } ;

/* Variables and functions */
#define  CONNECTED 138 
 int DISCONNECT_SCHEDULED ; 
#define  ERR_DISCONNECT 137 
#define  ERR_DISCONNECTED 136 
#define  ERR_DISCONNECT_RECONNECT 135 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  NO_QUEUE 134 
 int SCHEDULE_DISCONNECT ; 
#define  SRP_PROCESSING 133 
#define  UNCONFIGURING 132 
#define  UNDEFINED 131 
#define  WAIT_CONNECTION 130 
#define  WAIT_ENABLED 129 
#define  WAIT_IDLE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ibmvscsis_disconnect ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvscsis_post_disconnect(struct scsi_info *vscsi, uint new_state,
				      uint flag_bits)
{
	uint state;

	/* check the validity of the new state */
	switch (new_state) {
	case UNCONFIGURING:
	case ERR_DISCONNECT:
	case ERR_DISCONNECT_RECONNECT:
	case WAIT_IDLE:
		break;

	default:
		dev_err(&vscsi->dev, "post_disconnect: Invalid new state %d\n",
			new_state);
		return;
	}

	vscsi->flags |= flag_bits;

	dev_dbg(&vscsi->dev, "post_disconnect: new_state 0x%x, flag_bits 0x%x, vscsi->flags 0x%x, state %hx\n",
		new_state, flag_bits, vscsi->flags, vscsi->state);

	if (!(vscsi->flags & (DISCONNECT_SCHEDULED | SCHEDULE_DISCONNECT))) {
		vscsi->flags |= SCHEDULE_DISCONNECT;
		vscsi->new_state = new_state;

		INIT_WORK(&vscsi->proc_work, ibmvscsis_disconnect);
		(void)queue_work(vscsi->work_q, &vscsi->proc_work);
	} else {
		if (vscsi->new_state)
			state = vscsi->new_state;
		else
			state = vscsi->state;

		switch (state) {
		case NO_QUEUE:
		case UNCONFIGURING:
			break;

		case ERR_DISCONNECTED:
		case ERR_DISCONNECT:
		case UNDEFINED:
			if (new_state == UNCONFIGURING)
				vscsi->new_state = new_state;
			break;

		case ERR_DISCONNECT_RECONNECT:
			switch (new_state) {
			case UNCONFIGURING:
			case ERR_DISCONNECT:
				vscsi->new_state = new_state;
				break;
			default:
				break;
			}
			break;

		case WAIT_ENABLED:
		case WAIT_IDLE:
		case WAIT_CONNECTION:
		case CONNECTED:
		case SRP_PROCESSING:
			vscsi->new_state = new_state;
			break;

		default:
			break;
		}
	}

	dev_dbg(&vscsi->dev, "Leaving post_disconnect: flags 0x%x, new_state 0x%x\n",
		vscsi->flags, vscsi->new_state);
}