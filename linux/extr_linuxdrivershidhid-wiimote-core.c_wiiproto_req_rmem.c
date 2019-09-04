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
struct wiimote_data {int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int __u8 ;
typedef  int __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int WIIPROTO_REQ_RMEM ; 
 int /*<<< orphan*/  hid_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiimote_queue (struct wiimote_data*,int*,int) ; 
 int /*<<< orphan*/  wiiproto_keep_rumble (struct wiimote_data*,int*) ; 

void wiiproto_req_rmem(struct wiimote_data *wdata, bool eeprom, __u32 offset,
								__u16 size)
{
	__u8 cmd[7];

	if (size == 0) {
		hid_warn(wdata->hdev, "Invalid length %d rmem request\n", size);
		return;
	}

	cmd[0] = WIIPROTO_REQ_RMEM;
	cmd[1] = 0;
	cmd[2] = (offset >> 16) & 0xff;
	cmd[3] = (offset >> 8) & 0xff;
	cmd[4] = offset & 0xff;
	cmd[5] = (size >> 8) & 0xff;
	cmd[6] = size & 0xff;

	if (!eeprom)
		cmd[1] |= 0x04;

	wiiproto_keep_rumble(wdata, &cmd[1]);
	wiimote_queue(wdata, cmd, sizeof(cmd));
}