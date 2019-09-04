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
struct devfreq {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

int devfreq_remove_device(struct devfreq *devfreq)
{
	if (!devfreq)
		return -EINVAL;

	device_unregister(&devfreq->dev);

	return 0;
}