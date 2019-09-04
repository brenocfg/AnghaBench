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
struct acpi_smb_hc {int /*<<< orphan*/  done; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_transaction_complete(struct acpi_smb_hc *hc, int timeout)
{
	if (wait_event_timeout(hc->wait, hc->done, msecs_to_jiffies(timeout)))
		return 0;
	return -ETIME;
}