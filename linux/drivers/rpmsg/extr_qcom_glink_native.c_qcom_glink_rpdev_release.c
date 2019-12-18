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
struct rpmsg_device {int /*<<< orphan*/  ept; } ;
struct glink_channel {int /*<<< orphan*/ * rpdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpmsg_device*) ; 
 struct glink_channel* to_glink_channel (int /*<<< orphan*/ ) ; 
 struct rpmsg_device* to_rpmsg_device (struct device*) ; 

__attribute__((used)) static void qcom_glink_rpdev_release(struct device *dev)
{
	struct rpmsg_device *rpdev = to_rpmsg_device(dev);
	struct glink_channel *channel = to_glink_channel(rpdev->ept);

	channel->rpdev = NULL;
	kfree(rpdev);
}