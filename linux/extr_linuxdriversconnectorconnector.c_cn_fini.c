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
struct cn_dev {int /*<<< orphan*/  nls; int /*<<< orphan*/  cbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_net; } ;

/* Variables and functions */
 struct cn_dev cdev ; 
 scalar_t__ cn_already_initialized ; 
 int /*<<< orphan*/  cn_queue_free_dev (int /*<<< orphan*/ ) ; 
 TYPE_1__ init_net ; 
 int /*<<< orphan*/  netlink_kernel_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cn_fini(void)
{
	struct cn_dev *dev = &cdev;

	cn_already_initialized = 0;

	remove_proc_entry("connector", init_net.proc_net);

	cn_queue_free_dev(dev->cbdev);
	netlink_kernel_release(dev->nls);
}