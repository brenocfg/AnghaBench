#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; } ;
struct TYPE_3__ {TYPE_2__ status_cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEV_CMD_PLATFORM_STATUS ; 
 int __sev_do_cmd_locked (int /*<<< orphan*/ ,TYPE_2__*,int*) ; 
 TYPE_1__* psp_master ; 

__attribute__((used)) static int sev_get_platform_state(int *state, int *error)
{
	int rc;

	rc = __sev_do_cmd_locked(SEV_CMD_PLATFORM_STATUS,
				 &psp_master->status_cmd_buf, error);
	if (rc)
		return rc;

	*state = psp_master->status_cmd_buf.state;
	return rc;
}