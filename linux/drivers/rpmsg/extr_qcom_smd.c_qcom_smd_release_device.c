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
struct rpmsg_device {int dummy; } ;
struct qcom_smd_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qcom_smd_device*) ; 
 struct rpmsg_device* to_rpmsg_device (struct device*) ; 
 struct qcom_smd_device* to_smd_device (struct rpmsg_device*) ; 

__attribute__((used)) static void qcom_smd_release_device(struct device *dev)
{
	struct rpmsg_device *rpdev = to_rpmsg_device(dev);
	struct qcom_smd_device *qsdev = to_smd_device(rpdev);

	kfree(qsdev);
}