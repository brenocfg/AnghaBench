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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct pvr2_hdw {int* cmd_buffer; int /*<<< orphan*/  ctl_lock; } ;

/* Variables and functions */
 int FX2CMD_REG_WRITE ; 
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVR2_DECOMPOSE_LE (int*,int,int /*<<< orphan*/ ) ; 
 int pvr2_send_request (struct pvr2_hdw*,int*,int,int*,int /*<<< orphan*/ ) ; 

int pvr2_write_register(struct pvr2_hdw *hdw, u16 reg, u32 data)
{
	int ret;

	LOCK_TAKE(hdw->ctl_lock);

	hdw->cmd_buffer[0] = FX2CMD_REG_WRITE;  /* write register prefix */
	PVR2_DECOMPOSE_LE(hdw->cmd_buffer,1,data);
	hdw->cmd_buffer[5] = 0;
	hdw->cmd_buffer[6] = (reg >> 8) & 0xff;
	hdw->cmd_buffer[7] = reg & 0xff;


	ret = pvr2_send_request(hdw, hdw->cmd_buffer, 8, hdw->cmd_buffer, 0);

	LOCK_GIVE(hdw->ctl_lock);

	return ret;
}