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
struct qmp {int /*<<< orphan*/  mbox_chan; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 struct qmp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qmp_close (struct qmp*) ; 
 int /*<<< orphan*/  qmp_cooling_devices_remove (struct qmp*) ; 
 int /*<<< orphan*/  qmp_pd_remove (struct qmp*) ; 
 int /*<<< orphan*/  qmp_qdss_clk_remove (struct qmp*) ; 

__attribute__((used)) static int qmp_remove(struct platform_device *pdev)
{
	struct qmp *qmp = platform_get_drvdata(pdev);

	qmp_qdss_clk_remove(qmp);
	qmp_pd_remove(qmp);
	qmp_cooling_devices_remove(qmp);

	qmp_close(qmp);
	mbox_free_channel(qmp->mbox_chan);

	return 0;
}