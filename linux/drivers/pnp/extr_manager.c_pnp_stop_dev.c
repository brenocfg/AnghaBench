#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pnp_dev {int /*<<< orphan*/  dev; TYPE_1__* protocol; } ;
struct TYPE_2__ {scalar_t__ (* disable ) (struct pnp_dev*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pnp_can_disable (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ stub1 (struct pnp_dev*) ; 

int pnp_stop_dev(struct pnp_dev *dev)
{
	if (!pnp_can_disable(dev)) {
		pnp_dbg(&dev->dev, "disabling not supported\n");
		return -EINVAL;
	}
	if (dev->protocol->disable(dev) < 0) {
		dev_err(&dev->dev, "disable failed\n");
		return -EIO;
	}

	dev_info(&dev->dev, "disabled\n");
	return 0;
}