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
struct rtw_fw_state {int /*<<< orphan*/  completion; } ;
struct rtw_dev {int /*<<< orphan*/  dev; struct rtw_fw_state fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_load_firmware_cb ; 

__attribute__((used)) static int rtw_load_firmware(struct rtw_dev *rtwdev, const char *fw_name)
{
	struct rtw_fw_state *fw = &rtwdev->fw;
	int ret;

	init_completion(&fw->completion);

	ret = request_firmware_nowait(THIS_MODULE, true, fw_name, rtwdev->dev,
				      GFP_KERNEL, rtwdev, rtw_load_firmware_cb);
	if (ret) {
		rtw_err(rtwdev, "async firmware request failed\n");
		return ret;
	}

	return 0;
}