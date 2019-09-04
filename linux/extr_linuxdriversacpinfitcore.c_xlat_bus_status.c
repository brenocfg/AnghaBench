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
typedef  int u32 ;
typedef  int u16 ;
struct nd_cmd_clear_error {int cleared; int length; } ;
struct nd_cmd_ars_status {int out_length; int flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EIO ; 
 int ENOSPC ; 
 int ENOTTY ; 
 int ND_ARS_PERSISTENT ; 
 int ND_ARS_VOLATILE ; 
#define  ND_CMD_ARS_CAP 131 
#define  ND_CMD_ARS_START 130 
#define  ND_CMD_ARS_STATUS 129 
#define  ND_CMD_CLEAR_ERROR 128 
 int NFIT_ARS_CAP_NONE ; 
 int NFIT_ARS_F_OVERFLOW ; 
 int NFIT_ARS_START_BUSY ; 
 int NFIT_ARS_STATUS_BUSY ; 
 int NFIT_ARS_STATUS_DONE ; 
 int NFIT_ARS_STATUS_INTR ; 
 int NFIT_ARS_STATUS_NONE ; 

__attribute__((used)) static int xlat_bus_status(void *buf, unsigned int cmd, u32 status)
{
	struct nd_cmd_clear_error *clear_err;
	struct nd_cmd_ars_status *ars_status;
	u16 flags;

	switch (cmd) {
	case ND_CMD_ARS_CAP:
		if ((status & 0xffff) == NFIT_ARS_CAP_NONE)
			return -ENOTTY;

		/* Command failed */
		if (status & 0xffff)
			return -EIO;

		/* No supported scan types for this range */
		flags = ND_ARS_PERSISTENT | ND_ARS_VOLATILE;
		if ((status >> 16 & flags) == 0)
			return -ENOTTY;
		return 0;
	case ND_CMD_ARS_START:
		/* ARS is in progress */
		if ((status & 0xffff) == NFIT_ARS_START_BUSY)
			return -EBUSY;

		/* Command failed */
		if (status & 0xffff)
			return -EIO;
		return 0;
	case ND_CMD_ARS_STATUS:
		ars_status = buf;
		/* Command failed */
		if (status & 0xffff)
			return -EIO;
		/* Check extended status (Upper two bytes) */
		if (status == NFIT_ARS_STATUS_DONE)
			return 0;

		/* ARS is in progress */
		if (status == NFIT_ARS_STATUS_BUSY)
			return -EBUSY;

		/* No ARS performed for the current boot */
		if (status == NFIT_ARS_STATUS_NONE)
			return -EAGAIN;

		/*
		 * ARS interrupted, either we overflowed or some other
		 * agent wants the scan to stop.  If we didn't overflow
		 * then just continue with the returned results.
		 */
		if (status == NFIT_ARS_STATUS_INTR) {
			if (ars_status->out_length >= 40 && (ars_status->flags
						& NFIT_ARS_F_OVERFLOW))
				return -ENOSPC;
			return 0;
		}

		/* Unknown status */
		if (status >> 16)
			return -EIO;
		return 0;
	case ND_CMD_CLEAR_ERROR:
		clear_err = buf;
		if (status & 0xffff)
			return -EIO;
		if (!clear_err->cleared)
			return -EIO;
		if (clear_err->length > clear_err->cleared)
			return clear_err->cleared;
		return 0;
	default:
		break;
	}

	/* all other non-zero status results in an error */
	if (status)
		return -EIO;
	return 0;
}