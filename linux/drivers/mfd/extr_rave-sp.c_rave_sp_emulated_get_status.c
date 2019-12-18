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
struct rave_sp_status {int /*<<< orphan*/  bootloader_version; int /*<<< orphan*/  firmware_version; } ;
struct rave_sp {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int RAVE_SP_CMD_GET_BOOTLOADER_VERSION ; 
 int RAVE_SP_CMD_GET_FIRMWARE_VERSION ; 
 int rave_sp_exec (struct rave_sp*,int*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rave_sp_emulated_get_status(struct rave_sp *sp,
				       struct rave_sp_status *status)
{
	u8 cmd[] = {
		[0] = RAVE_SP_CMD_GET_FIRMWARE_VERSION,
		[1] = 0,
	};
	int ret;

	ret = rave_sp_exec(sp, cmd, sizeof(cmd), &status->firmware_version,
			   sizeof(status->firmware_version));
	if (ret)
		return ret;

	cmd[0] = RAVE_SP_CMD_GET_BOOTLOADER_VERSION;
	return rave_sp_exec(sp, cmd, sizeof(cmd), &status->bootloader_version,
			    sizeof(status->bootloader_version));
}