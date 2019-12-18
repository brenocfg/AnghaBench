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
struct TYPE_2__ {int code; } ;
struct ucsi_ccg {int cmd_resp; TYPE_1__ dev_resp; int /*<<< orphan*/  flags; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ASYNC_EVENT ; 
 int /*<<< orphan*/  DEV_CMD_PENDING ; 
 int RESET_COMPLETE ; 
 int /*<<< orphan*/  RESET_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  get_fw_info (struct ucsi_ccg*) ; 
 scalar_t__ invalid_async_evt (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccg_process_response(struct ucsi_ccg *uc)
{
	struct device *dev = uc->dev;

	if (uc->dev_resp.code & ASYNC_EVENT) {
		if (uc->dev_resp.code == RESET_COMPLETE) {
			if (test_bit(RESET_PENDING, &uc->flags))
				uc->cmd_resp = uc->dev_resp.code;
			get_fw_info(uc);
		}
		if (invalid_async_evt(uc->dev_resp.code))
			dev_err(dev, "invalid async evt %d\n",
				uc->dev_resp.code);
	} else {
		if (test_bit(DEV_CMD_PENDING, &uc->flags)) {
			uc->cmd_resp = uc->dev_resp.code;
			clear_bit(DEV_CMD_PENDING, &uc->flags);
		} else {
			dev_err(dev, "dev resp 0x%04x but no cmd pending\n",
				uc->dev_resp.code);
		}
	}
}