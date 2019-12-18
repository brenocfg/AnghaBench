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
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct cros_ec_rpmsg {int /*<<< orphan*/  host_event_work; int /*<<< orphan*/  ept; } ;
struct cros_ec_device {struct cros_ec_rpmsg* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cros_ec_unregister (struct cros_ec_device*) ; 
 struct cros_ec_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmsg_destroy_ept (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cros_ec_rpmsg_remove(struct rpmsg_device *rpdev)
{
	struct cros_ec_device *ec_dev = dev_get_drvdata(&rpdev->dev);
	struct cros_ec_rpmsg *ec_rpmsg = ec_dev->priv;

	cros_ec_unregister(ec_dev);
	rpmsg_destroy_ept(ec_rpmsg->ept);
	cancel_work_sync(&ec_rpmsg->host_event_work);
}