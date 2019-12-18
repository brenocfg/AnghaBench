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
struct pvscsi_adapter {int dummy; } ;
struct PVSCSICmdDescResetDevice {int /*<<< orphan*/  target; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_CMD_RESET_DEVICE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_dev (struct pvscsi_adapter const*) ; 
 int /*<<< orphan*/  pvscsi_write_cmd_desc (struct pvscsi_adapter const*,int /*<<< orphan*/ ,struct PVSCSICmdDescResetDevice*,int) ; 

__attribute__((used)) static void ll_device_reset(const struct pvscsi_adapter *adapter, u32 target)
{
	struct PVSCSICmdDescResetDevice cmd = { 0 };

	dev_dbg(pvscsi_dev(adapter), "Resetting device: target=%u\n", target);

	cmd.target = target;

	pvscsi_write_cmd_desc(adapter, PVSCSI_CMD_RESET_DEVICE,
			      &cmd, sizeof(cmd));
}