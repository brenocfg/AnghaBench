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
struct hci_dev {int dummy; } ;
struct device {int dummy; } ;
struct btmtkuart_dev {TYPE_1__* serdev; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct btmtkuart_dev* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  serdev_device_close (TYPE_1__*) ; 

__attribute__((used)) static int btmtkuart_close(struct hci_dev *hdev)
{
	struct btmtkuart_dev *bdev = hci_get_drvdata(hdev);
	struct device *dev = &bdev->serdev->dev;

	/* Shutdown the clock and power domain the device requires */
	clk_disable_unprepare(bdev->clk);
	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);

	serdev_device_close(bdev->serdev);

	return 0;
}