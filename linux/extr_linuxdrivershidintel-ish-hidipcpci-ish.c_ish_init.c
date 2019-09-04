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
struct ishtp_device {int /*<<< orphan*/  devc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ish_hw_start (struct ishtp_device*) ; 
 int ishtp_start (struct ishtp_device*) ; 

__attribute__((used)) static int ish_init(struct ishtp_device *dev)
{
	int ret;

	/* Set the state of ISH HW to start */
	ret = ish_hw_start(dev);
	if (ret) {
		dev_err(dev->devc, "ISH: hw start failed.\n");
		return ret;
	}

	/* Start the inter process communication to ISH processor */
	ret = ishtp_start(dev);
	if (ret) {
		dev_err(dev->devc, "ISHTP: Protocol init failed.\n");
		return ret;
	}

	return 0;
}