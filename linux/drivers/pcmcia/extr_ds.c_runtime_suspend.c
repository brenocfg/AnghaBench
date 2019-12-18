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

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int pcmcia_dev_suspend (struct device*) ; 

__attribute__((used)) static int runtime_suspend(struct device *dev)
{
	int rc;

	device_lock(dev);
	rc = pcmcia_dev_suspend(dev);
	device_unlock(dev);
	return rc;
}