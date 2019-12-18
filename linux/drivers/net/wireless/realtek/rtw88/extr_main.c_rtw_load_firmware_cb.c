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
struct rtw_fw_state {int /*<<< orphan*/  completion; struct firmware const* firmware; } ;
struct rtw_dev {struct rtw_fw_state fw; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 

__attribute__((used)) static void rtw_load_firmware_cb(const struct firmware *firmware, void *context)
{
	struct rtw_dev *rtwdev = context;
	struct rtw_fw_state *fw = &rtwdev->fw;

	if (!firmware)
		rtw_err(rtwdev, "failed to request firmware\n");

	fw->firmware = firmware;
	complete_all(&fw->completion);
}