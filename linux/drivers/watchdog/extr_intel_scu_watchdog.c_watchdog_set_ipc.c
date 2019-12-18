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
typedef  char u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_SET_WATCHDOG_TIMER ; 
 int intel_scu_ipc_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int watchdog_set_ipc(int soft_threshold, int threshold)
{
	u32	*ipc_wbuf;
	u8	 cbuf[16] = { '\0' };
	int	 ipc_ret = 0;

	ipc_wbuf = (u32 *)&cbuf;
	ipc_wbuf[0] = soft_threshold;
	ipc_wbuf[1] = threshold;

	ipc_ret = intel_scu_ipc_command(
			IPC_SET_WATCHDOG_TIMER,
			0,
			ipc_wbuf,
			2,
			NULL,
			0);

	if (ipc_ret != 0)
		pr_err("Error setting SCU watchdog timer: %x\n", ipc_ret);

	return ipc_ret;
}