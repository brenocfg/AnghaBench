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
struct ipw_priv {int status; int /*<<< orphan*/  scan_check; int /*<<< orphan*/  adapter_restart; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_SCAN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPW_SCAN_CHECK_WATCHDOG ; 
 int STATUS_SCANNING ; 
 int STATUS_SCAN_ABORTING ; 
 int /*<<< orphan*/  ipw_abort_scan (struct ipw_priv*) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipw_scan_check(void *data)
{
	struct ipw_priv *priv = data;

	if (priv->status & STATUS_SCAN_ABORTING) {
		IPW_DEBUG_SCAN("Scan completion watchdog resetting "
			       "adapter after (%dms).\n",
			       jiffies_to_msecs(IPW_SCAN_CHECK_WATCHDOG));
		schedule_work(&priv->adapter_restart);
	} else if (priv->status & STATUS_SCANNING) {
		IPW_DEBUG_SCAN("Scan completion watchdog aborting scan "
			       "after (%dms).\n",
			       jiffies_to_msecs(IPW_SCAN_CHECK_WATCHDOG));
		ipw_abort_scan(priv);
		schedule_delayed_work(&priv->scan_check, HZ);
	}
}