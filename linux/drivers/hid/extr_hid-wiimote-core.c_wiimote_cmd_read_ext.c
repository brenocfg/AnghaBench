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
typedef  int __u8 ;

/* Variables and functions */
 int WIIMOTE_EXT_BALANCE_BOARD ; 
 int WIIMOTE_EXT_CLASSIC_CONTROLLER ; 
 int WIIMOTE_EXT_DRUMS ; 
 int WIIMOTE_EXT_GUITAR ; 
 int WIIMOTE_EXT_NONE ; 
 int WIIMOTE_EXT_NUNCHUK ; 
 int WIIMOTE_EXT_PRO_CONTROLLER ; 
 int WIIMOTE_EXT_UNKNOWN ; 
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*,int*) ; 
 int wiimote_cmd_read (struct wiimote_data*,int,int*,int) ; 

__attribute__((used)) static __u8 wiimote_cmd_read_ext(struct wiimote_data *wdata, __u8 *rmem)
{
	int ret;

	/* read extension ID */
	ret = wiimote_cmd_read(wdata, 0xa400fa, rmem, 6);
	if (ret != 6)
		return WIIMOTE_EXT_NONE;

	hid_dbg(wdata->hdev, "extension ID: %6phC\n", rmem);

	if (rmem[0] == 0xff && rmem[1] == 0xff && rmem[2] == 0xff &&
	    rmem[3] == 0xff && rmem[4] == 0xff && rmem[5] == 0xff)
		return WIIMOTE_EXT_NONE;

	if (rmem[4] == 0x00 && rmem[5] == 0x00)
		return WIIMOTE_EXT_NUNCHUK;
	if (rmem[4] == 0x01 && rmem[5] == 0x01)
		return WIIMOTE_EXT_CLASSIC_CONTROLLER;
	if (rmem[4] == 0x04 && rmem[5] == 0x02)
		return WIIMOTE_EXT_BALANCE_BOARD;
	if (rmem[4] == 0x01 && rmem[5] == 0x20)
		return WIIMOTE_EXT_PRO_CONTROLLER;
	if (rmem[0] == 0x01 && rmem[1] == 0x00 &&
	    rmem[4] == 0x01 && rmem[5] == 0x03)
		return WIIMOTE_EXT_DRUMS;
	if (rmem[0] == 0x00 && rmem[1] == 0x00 &&
	    rmem[4] == 0x01 && rmem[5] == 0x03)
		return WIIMOTE_EXT_GUITAR;

	return WIIMOTE_EXT_UNKNOWN;
}