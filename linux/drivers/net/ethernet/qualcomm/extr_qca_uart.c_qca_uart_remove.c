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
struct serdev_device {int dummy; } ;
struct qcauart {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_close (struct serdev_device*) ; 
 struct qcauart* serdev_device_get_drvdata (struct serdev_device*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qca_uart_remove(struct serdev_device *serdev)
{
	struct qcauart *qca = serdev_device_get_drvdata(serdev);

	unregister_netdev(qca->net_dev);

	/* Flush any pending characters in the driver. */
	serdev_device_close(serdev);
	cancel_work_sync(&qca->tx_work);

	free_netdev(qca->net_dev);
}