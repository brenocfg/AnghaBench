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
struct isci_remote_device {scalar_t__ started_request_count; int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SCI_DEV_STOPPED ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rnc_destruct_done(void *_dev)
{
	struct isci_remote_device *idev = _dev;

	BUG_ON(idev->started_request_count != 0);
	sci_change_state(&idev->sm, SCI_DEV_STOPPED);
}