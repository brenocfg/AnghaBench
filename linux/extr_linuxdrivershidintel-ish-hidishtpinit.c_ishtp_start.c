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
struct ishtp_device {int /*<<< orphan*/  dev_state; int /*<<< orphan*/  devc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ISHTP_DEV_DISABLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ishtp_hbm_start_wait (struct ishtp_device*) ; 
 int /*<<< orphan*/  ishtp_query_subscribers (struct ishtp_device*) ; 

int ishtp_start(struct ishtp_device *dev)
{
	if (ishtp_hbm_start_wait(dev)) {
		dev_err(dev->devc, "HBM haven't started");
		goto err;
	}

	/* suspend & resume notification - send QUERY_SUBSCRIBERS msg */
	ishtp_query_subscribers(dev);

	return 0;
err:
	dev_err(dev->devc, "link layer initialization failed.\n");
	dev->dev_state = ISHTP_DEV_DISABLED;
	return -ENODEV;
}