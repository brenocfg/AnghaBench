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
struct device {int dummy; } ;
struct coresight_device {struct coresight_device* refcnt; struct coresight_device* conns; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct coresight_device*) ; 
 struct coresight_device* to_coresight_device (struct device*) ; 

__attribute__((used)) static void coresight_device_release(struct device *dev)
{
	struct coresight_device *csdev = to_coresight_device(dev);

	kfree(csdev->conns);
	kfree(csdev->refcnt);
	kfree(csdev);
}