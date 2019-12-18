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
typedef  int u8 ;
typedef  int u16 ;
struct pvr2_hdw {int* cmd_buffer; int /*<<< orphan*/  ctl_lock; } ;

/* Variables and functions */
 int EIO ; 
 int ENOTSUPP ; 
 int FX2CMD_I2C_WRITE ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int pvr2_send_request (struct pvr2_hdw*,int*,int,int*,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int,int,unsigned int) ; 
 int /*<<< orphan*/  trace_i2c (char*,int,int) ; 

__attribute__((used)) static int pvr2_i2c_write(struct pvr2_hdw *hdw, /* Context */
			  u8 i2c_addr,      /* I2C address we're talking to */
			  u8 *data,         /* Data to write */
			  u16 length)       /* Size of data to write */
{
	/* Return value - default 0 means success */
	int ret;


	if (!data) length = 0;
	if (length > (sizeof(hdw->cmd_buffer) - 3)) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Killing an I2C write to %u that is too large (desired=%u limit=%u)",
			   i2c_addr,
			   length,(unsigned int)(sizeof(hdw->cmd_buffer) - 3));
		return -ENOTSUPP;
	}

	LOCK_TAKE(hdw->ctl_lock);

	/* Clear the command buffer (likely to be paranoia) */
	memset(hdw->cmd_buffer, 0, sizeof(hdw->cmd_buffer));

	/* Set up command buffer for an I2C write */
	hdw->cmd_buffer[0] = FX2CMD_I2C_WRITE;      /* write prefix */
	hdw->cmd_buffer[1] = i2c_addr;  /* i2c addr of chip */
	hdw->cmd_buffer[2] = length;    /* length of what follows */
	if (length) memcpy(hdw->cmd_buffer + 3, data, length);

	/* Do the operation */
	ret = pvr2_send_request(hdw,
				hdw->cmd_buffer,
				length + 3,
				hdw->cmd_buffer,
				1);
	if (!ret) {
		if (hdw->cmd_buffer[0] != 8) {
			ret = -EIO;
			if (hdw->cmd_buffer[0] != 7) {
				trace_i2c("unexpected status from i2_write[%d]: %d",
					  i2c_addr,hdw->cmd_buffer[0]);
			}
		}
	}

	LOCK_GIVE(hdw->ctl_lock);

	return ret;
}