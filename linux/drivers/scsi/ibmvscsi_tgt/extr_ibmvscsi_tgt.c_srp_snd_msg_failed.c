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
struct TYPE_2__ {scalar_t__ timer_pops; int started; int /*<<< orphan*/  timer; } ;
struct scsi_info {int flags; int state; int /*<<< orphan*/  dev; TYPE_1__ rsp_q_timer; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int CLIENT_FAILED ; 
 int ERR_DISCONNECT ; 
 int ERR_DISCONNECTED ; 
 int ERR_DISCONNECT_RECONNECT ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 long H_CLOSED ; 
 long H_DROPPED ; 
 scalar_t__ MAX_TIMER_POPS ; 
 int RESPONSE_Q_DOWN ; 
 scalar_t__ SRP_PROCESSING ; 
 int UNDEFINED ; 
 int /*<<< orphan*/  WAIT_NANO_SECONDS ; 
 int /*<<< orphan*/  WAIT_SECONDS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_free_cmd_qs (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_snd_msg_failed(struct scsi_info *vscsi, long rc)
{
	ktime_t kt;

	if (rc != H_DROPPED) {
		ibmvscsis_free_cmd_qs(vscsi);

		if (rc == H_CLOSED)
			vscsi->flags |= CLIENT_FAILED;

		/* don't flag the same problem multiple times */
		if (!(vscsi->flags & RESPONSE_Q_DOWN)) {
			vscsi->flags |= RESPONSE_Q_DOWN;
			if (!(vscsi->state & (ERR_DISCONNECT |
					      ERR_DISCONNECT_RECONNECT |
					      ERR_DISCONNECTED | UNDEFINED))) {
				dev_err(&vscsi->dev, "snd_msg_failed: setting RESPONSE_Q_DOWN, state 0x%hx, flags 0x%x, rc %ld\n",
					vscsi->state, vscsi->flags, rc);
			}
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
		}
		return;
	}

	/*
	 * The response queue is full.
	 * If the server is processing SRP requests, i.e.
	 * the client has successfully done an
	 * SRP_LOGIN, then it will wait forever for room in
	 * the queue.  However if the system admin
	 * is attempting to unconfigure the server then one
	 * or more children will be in a state where
	 * they are being removed. So if there is even one
	 * child being removed then the driver assumes
	 * the system admin is attempting to break the
	 * connection with the client and MAX_TIMER_POPS
	 * is honored.
	 */
	if ((vscsi->rsp_q_timer.timer_pops < MAX_TIMER_POPS) ||
	    (vscsi->state == SRP_PROCESSING)) {
		dev_dbg(&vscsi->dev, "snd_msg_failed: response queue full, flags 0x%x, timer started %d, pops %d\n",
			vscsi->flags, (int)vscsi->rsp_q_timer.started,
			vscsi->rsp_q_timer.timer_pops);

		/*
		 * Check if the timer is running; if it
		 * is not then start it up.
		 */
		if (!vscsi->rsp_q_timer.started) {
			if (vscsi->rsp_q_timer.timer_pops <
			    MAX_TIMER_POPS) {
				kt = WAIT_NANO_SECONDS;
			} else {
				/*
				 * slide the timeslice if the maximum
				 * timer pops have already happened
				 */
				kt = ktime_set(WAIT_SECONDS, 0);
			}

			vscsi->rsp_q_timer.started = true;
			hrtimer_start(&vscsi->rsp_q_timer.timer, kt,
				      HRTIMER_MODE_REL);
		}
	} else {
		/*
		 * TBD: Do we need to worry about this? Need to get
		 *      remove working.
		 */
		/*
		 * waited a long time and it appears the system admin
		 * is bring this driver down
		 */
		vscsi->flags |= RESPONSE_Q_DOWN;
		ibmvscsis_free_cmd_qs(vscsi);
		/*
		 * if the driver is already attempting to disconnect
		 * from the client and has already logged an error
		 * trace this event but don't put it in the error log
		 */
		if (!(vscsi->state & (ERR_DISCONNECT |
				      ERR_DISCONNECT_RECONNECT |
				      ERR_DISCONNECTED | UNDEFINED))) {
			dev_err(&vscsi->dev, "client crq full too long\n");
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT,
						  0);
		}
	}
}