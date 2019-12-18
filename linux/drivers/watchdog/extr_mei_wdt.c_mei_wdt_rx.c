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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ command; scalar_t__ versionnumber; scalar_t__ subcommand; } ;
struct mei_wdt_start_response {int wdstate; TYPE_1__ hdr; } ;
struct mei_wdt {scalar_t__ state; int /*<<< orphan*/  response; int /*<<< orphan*/  unregister; int /*<<< orphan*/  cldev; } ;
struct mei_mc_hdr {int dummy; } ;
struct mei_cl_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 scalar_t__ MEI_MANAGEMENT_CONTROL ; 
 scalar_t__ MEI_MC_START_WD_TIMER_RES ; 
 scalar_t__ MEI_MC_VERSION_NUMBER ; 
 void* MEI_WDT_NOT_REQUIRED ; 
 scalar_t__ MEI_WDT_PROBE ; 
 scalar_t__ MEI_WDT_RUNNING ; 
 int MEI_WDT_WDSTATE_NOT_REQUIRED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,...) ; 
 struct mei_wdt* mei_cldev_get_drvdata (struct mei_cl_device*) ; 
 int mei_cldev_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  mei_wdt_register (struct mei_wdt*) ; 
 int /*<<< orphan*/  mei_wdt_state_str (scalar_t__) ; 
 int /*<<< orphan*/  mei_wdt_stop (struct mei_wdt*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mei_wdt_rx(struct mei_cl_device *cldev)
{
	struct mei_wdt *wdt = mei_cldev_get_drvdata(cldev);
	struct mei_wdt_start_response res;
	const size_t res_len = sizeof(res);
	int ret;

	ret = mei_cldev_recv(wdt->cldev, (u8 *)&res, res_len);
	if (ret < 0) {
		dev_err(&cldev->dev, "failure in recv %d\n", ret);
		return;
	}

	/* Empty response can be sent on stop */
	if (ret == 0)
		return;

	if (ret < sizeof(struct mei_mc_hdr)) {
		dev_err(&cldev->dev, "recv small data %d\n", ret);
		return;
	}

	if (res.hdr.command != MEI_MANAGEMENT_CONTROL ||
	    res.hdr.versionnumber != MEI_MC_VERSION_NUMBER) {
		dev_err(&cldev->dev, "wrong command received\n");
		return;
	}

	if (res.hdr.subcommand != MEI_MC_START_WD_TIMER_RES) {
		dev_warn(&cldev->dev, "unsupported command %d :%s[%d]\n",
			 res.hdr.subcommand,
			 mei_wdt_state_str(wdt->state),
			 wdt->state);
		return;
	}

	/* Run the unregistration in a worker as this can be
	 * run only after ping completion, otherwise the flow will
	 * deadlock on watchdog core mutex.
	 */
	if (wdt->state == MEI_WDT_RUNNING) {
		if (res.wdstate & MEI_WDT_WDSTATE_NOT_REQUIRED) {
			wdt->state = MEI_WDT_NOT_REQUIRED;
			schedule_work(&wdt->unregister);
		}
		goto out;
	}

	if (wdt->state == MEI_WDT_PROBE) {
		if (res.wdstate & MEI_WDT_WDSTATE_NOT_REQUIRED) {
			wdt->state = MEI_WDT_NOT_REQUIRED;
		} else {
			/* stop the watchdog and register watchdog device */
			mei_wdt_stop(wdt);
			mei_wdt_register(wdt);
		}
		return;
	}

	dev_warn(&cldev->dev, "not in correct state %s[%d]\n",
			 mei_wdt_state_str(wdt->state), wdt->state);

out:
	if (!completion_done(&wdt->response))
		complete(&wdt->response);
}