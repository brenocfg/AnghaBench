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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  sev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEV_CMD_SHUTDOWN ; 
 int /*<<< orphan*/  SEV_STATE_UNINIT ; 
 int __sev_do_cmd_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* psp_master ; 

__attribute__((used)) static int __sev_platform_shutdown_locked(int *error)
{
	int ret;

	ret = __sev_do_cmd_locked(SEV_CMD_SHUTDOWN, NULL, error);
	if (ret)
		return ret;

	psp_master->sev_state = SEV_STATE_UNINIT;
	dev_dbg(psp_master->dev, "SEV firmware shutdown\n");

	return ret;
}