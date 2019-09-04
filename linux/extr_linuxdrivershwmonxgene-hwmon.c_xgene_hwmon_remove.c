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
struct xgene_hwmon_dev {int /*<<< orphan*/  mbox_chan; int /*<<< orphan*/  async_msg_fifo; int /*<<< orphan*/  hwmon_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_disabled ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcc_mbox_free_channel (int /*<<< orphan*/ ) ; 
 struct xgene_hwmon_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int xgene_hwmon_remove(struct platform_device *pdev)
{
	struct xgene_hwmon_dev *ctx = platform_get_drvdata(pdev);

	hwmon_device_unregister(ctx->hwmon_dev);
	kfifo_free(&ctx->async_msg_fifo);
	if (acpi_disabled)
		mbox_free_channel(ctx->mbox_chan);
	else
		pcc_mbox_free_channel(ctx->mbox_chan);

	return 0;
}