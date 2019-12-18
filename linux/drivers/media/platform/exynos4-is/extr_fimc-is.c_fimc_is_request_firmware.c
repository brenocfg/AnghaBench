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
struct fimc_is {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_ACTION_HOTPLUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  fimc_is_load_firmware ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fimc_is*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_is_request_firmware(struct fimc_is *is, const char *fw_name)
{
	return request_firmware_nowait(THIS_MODULE,
				FW_ACTION_HOTPLUG, fw_name, &is->pdev->dev,
				GFP_KERNEL, is, fimc_is_load_firmware);
}