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

/* Variables and functions */
 long OPAL_BUSY ; 
 long OPAL_BUSY_EVENT ; 
 int /*<<< orphan*/  OPAL_DUMP_REGION_LOG_BUF ; 
 int /*<<< orphan*/  OPAL_UNREGISTER_DUMP_REGION ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ opal_check_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_event_shutdown () ; 
 int /*<<< orphan*/  opal_poll_events (int /*<<< orphan*/ *) ; 
 long opal_sync_host_reboot () ; 
 int /*<<< orphan*/  opal_unregister_dump_region (int /*<<< orphan*/ ) ; 

void opal_shutdown(void)
{
	long rc = OPAL_BUSY;

	opal_event_shutdown();

	/*
	 * Then sync with OPAL which ensure anything that can
	 * potentially write to our memory has completed such
	 * as an ongoing dump retrieval
	 */
	while (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) {
		rc = opal_sync_host_reboot();
		if (rc == OPAL_BUSY)
			opal_poll_events(NULL);
		else
			mdelay(10);
	}

	/* Unregister memory dump region */
	if (opal_check_token(OPAL_UNREGISTER_DUMP_REGION))
		opal_unregister_dump_region(OPAL_DUMP_REGION_LOG_BUF);
}