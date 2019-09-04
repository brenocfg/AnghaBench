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
struct psp_device {scalar_t__ sev_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  init_cmd_buf; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SEV_CMD_INIT ; 
 scalar_t__ SEV_STATE_INIT ; 
 int __sev_do_cmd_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct psp_device* psp_master ; 

__attribute__((used)) static int __sev_platform_init_locked(int *error)
{
	struct psp_device *psp = psp_master;
	int rc = 0;

	if (!psp)
		return -ENODEV;

	if (psp->sev_state == SEV_STATE_INIT)
		return 0;

	rc = __sev_do_cmd_locked(SEV_CMD_INIT, &psp->init_cmd_buf, error);
	if (rc)
		return rc;

	psp->sev_state = SEV_STATE_INIT;
	dev_dbg(psp->dev, "SEV firmware initialized\n");

	return rc;
}