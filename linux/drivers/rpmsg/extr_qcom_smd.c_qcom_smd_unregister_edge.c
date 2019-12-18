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
struct qcom_smd_edge {int /*<<< orphan*/  dev; int /*<<< orphan*/  mbox_chan; int /*<<< orphan*/  state_work; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_remove_device ; 

int qcom_smd_unregister_edge(struct qcom_smd_edge *edge)
{
	int ret;

	disable_irq(edge->irq);
	cancel_work_sync(&edge->scan_work);
	cancel_work_sync(&edge->state_work);

	ret = device_for_each_child(&edge->dev, NULL, qcom_smd_remove_device);
	if (ret)
		dev_warn(&edge->dev, "can't remove smd device: %d\n", ret);

	mbox_free_channel(edge->mbox_chan);
	device_unregister(&edge->dev);

	return 0;
}