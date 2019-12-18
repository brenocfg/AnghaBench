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
struct qtnf_wmac {int /*<<< orphan*/  scan_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_mac_scan_finish (struct qtnf_wmac*,int) ; 

void qtnf_scan_done(struct qtnf_wmac *mac, bool aborted)
{
	cancel_delayed_work_sync(&mac->scan_timeout);
	qtnf_mac_scan_finish(mac, aborted);
}