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
struct mei_wdt {int /*<<< orphan*/  unregister; int /*<<< orphan*/  response; } ;
struct mei_cl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbgfs_unregister (struct mei_wdt*) ; 
 int /*<<< orphan*/  kfree (struct mei_wdt*) ; 
 int /*<<< orphan*/  mei_cldev_disable (struct mei_cl_device*) ; 
 struct mei_wdt* mei_cldev_get_drvdata (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_wdt_unregister (struct mei_wdt*) ; 

__attribute__((used)) static int mei_wdt_remove(struct mei_cl_device *cldev)
{
	struct mei_wdt *wdt = mei_cldev_get_drvdata(cldev);

	/* Free the caller in case of fw initiated or unexpected reset */
	if (!completion_done(&wdt->response))
		complete(&wdt->response);

	cancel_work_sync(&wdt->unregister);

	mei_wdt_unregister(wdt);

	mei_cldev_disable(cldev);

	dbgfs_unregister(wdt);

	kfree(wdt);

	return 0;
}