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
struct Scsi_Host {int shost_state; } ;
typedef  enum scsi_host_state { ____Placeholder_scsi_host_state } scsi_host_state ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  SCSI_LOG_ERROR_RECOVERY (int,int /*<<< orphan*/ ) ; 
#define  SHOST_CANCEL 134 
#define  SHOST_CANCEL_RECOVERY 133 
#define  SHOST_CREATED 132 
#define  SHOST_DEL 131 
#define  SHOST_DEL_RECOVERY 130 
#define  SHOST_RECOVERY 129 
#define  SHOST_RUNNING 128 
 int /*<<< orphan*/  scsi_host_state_name (int) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int scsi_host_set_state(struct Scsi_Host *shost, enum scsi_host_state state)
{
	enum scsi_host_state oldstate = shost->shost_state;

	if (state == oldstate)
		return 0;

	switch (state) {
	case SHOST_CREATED:
		/* There are no legal states that come back to
		 * created.  This is the manually initialised start
		 * state */
		goto illegal;

	case SHOST_RUNNING:
		switch (oldstate) {
		case SHOST_CREATED:
		case SHOST_RECOVERY:
			break;
		default:
			goto illegal;
		}
		break;

	case SHOST_RECOVERY:
		switch (oldstate) {
		case SHOST_RUNNING:
			break;
		default:
			goto illegal;
		}
		break;

	case SHOST_CANCEL:
		switch (oldstate) {
		case SHOST_CREATED:
		case SHOST_RUNNING:
		case SHOST_CANCEL_RECOVERY:
			break;
		default:
			goto illegal;
		}
		break;

	case SHOST_DEL:
		switch (oldstate) {
		case SHOST_CANCEL:
		case SHOST_DEL_RECOVERY:
			break;
		default:
			goto illegal;
		}
		break;

	case SHOST_CANCEL_RECOVERY:
		switch (oldstate) {
		case SHOST_CANCEL:
		case SHOST_RECOVERY:
			break;
		default:
			goto illegal;
		}
		break;

	case SHOST_DEL_RECOVERY:
		switch (oldstate) {
		case SHOST_CANCEL_RECOVERY:
			break;
		default:
			goto illegal;
		}
		break;
	}
	shost->shost_state = state;
	return 0;

 illegal:
	SCSI_LOG_ERROR_RECOVERY(1,
				shost_printk(KERN_ERR, shost,
					     "Illegal host state transition"
					     "%s->%s\n",
					     scsi_host_state_name(oldstate),
					     scsi_host_state_name(state)));
	return -EINVAL;
}