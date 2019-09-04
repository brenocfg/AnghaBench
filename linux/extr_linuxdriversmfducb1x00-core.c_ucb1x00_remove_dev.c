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
struct ucb1x00_dev {int /*<<< orphan*/  drv_node; int /*<<< orphan*/  dev_node; TYPE_1__* drv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct ucb1x00_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ucb1x00_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ucb1x00_dev*) ; 

__attribute__((used)) static void ucb1x00_remove_dev(struct ucb1x00_dev *dev)
{
	dev->drv->remove(dev);
	list_del(&dev->dev_node);
	list_del(&dev->drv_node);
	kfree(dev);
}