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
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  hid_info (int /*<<< orphan*/ ,char*,int*) ; 
 int wiimote_cmd_read (struct wiimote_data*,int,int*,int) ; 

__attribute__((used)) static bool wiimote_cmd_read_mp(struct wiimote_data *wdata, __u8 *rmem)
{
	int ret;

	/* read motion plus ID */
	ret = wiimote_cmd_read(wdata, 0xa600fa, rmem, 6);
	if (ret != 6)
		return false;

	hid_dbg(wdata->hdev, "motion plus ID: %6phC\n", rmem);

	if (rmem[5] == 0x05)
		return true;

	hid_info(wdata->hdev, "unknown motion plus ID: %6phC\n", rmem);

	return false;
}