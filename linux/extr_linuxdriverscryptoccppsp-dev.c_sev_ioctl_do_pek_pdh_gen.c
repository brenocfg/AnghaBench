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
struct sev_issue_cmd {int /*<<< orphan*/  error; } ;
struct TYPE_2__ {scalar_t__ sev_state; } ;

/* Variables and functions */
 scalar_t__ SEV_STATE_UNINIT ; 
 int __sev_do_cmd_locked (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int __sev_platform_init_locked (int /*<<< orphan*/ *) ; 
 TYPE_1__* psp_master ; 

__attribute__((used)) static int sev_ioctl_do_pek_pdh_gen(int cmd, struct sev_issue_cmd *argp)
{
	int rc;

	if (psp_master->sev_state == SEV_STATE_UNINIT) {
		rc = __sev_platform_init_locked(&argp->error);
		if (rc)
			return rc;
	}

	return __sev_do_cmd_locked(cmd, NULL, &argp->error);
}