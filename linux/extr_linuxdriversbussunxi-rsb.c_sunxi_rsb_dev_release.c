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
struct sunxi_rsb_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sunxi_rsb_device*) ; 
 struct sunxi_rsb_device* to_sunxi_rsb_device (struct device*) ; 

__attribute__((used)) static void sunxi_rsb_dev_release(struct device *dev)
{
	struct sunxi_rsb_device *rdev = to_sunxi_rsb_device(dev);

	kfree(rdev);
}