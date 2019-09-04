#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netlink_kernel_cfg {int /*<<< orphan*/  input; int /*<<< orphan*/  groups; } ;
struct cn_dev {int /*<<< orphan*/  nls; int /*<<< orphan*/  cbdev; int /*<<< orphan*/  input; } ;
struct TYPE_3__ {int /*<<< orphan*/  proc_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_NETLINK_USERS ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NETLINK_CONNECTOR ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct cn_dev cdev ; 
 int cn_already_initialized ; 
 int /*<<< orphan*/  cn_proc_show ; 
 int /*<<< orphan*/  cn_queue_alloc_dev (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ init_net ; 
 int /*<<< orphan*/  netlink_kernel_create (TYPE_1__*,int /*<<< orphan*/ ,struct netlink_kernel_cfg*) ; 
 int /*<<< orphan*/  netlink_kernel_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_create_single (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cn_init(void)
{
	struct cn_dev *dev = &cdev;
	struct netlink_kernel_cfg cfg = {
		.groups	= CN_NETLINK_USERS + 0xf,
		.input	= dev->input,
	};

	dev->nls = netlink_kernel_create(&init_net, NETLINK_CONNECTOR, &cfg);
	if (!dev->nls)
		return -EIO;

	dev->cbdev = cn_queue_alloc_dev("cqueue", dev->nls);
	if (!dev->cbdev) {
		netlink_kernel_release(dev->nls);
		return -EINVAL;
	}

	cn_already_initialized = 1;

	proc_create_single("connector", S_IRUGO, init_net.proc_net, cn_proc_show);

	return 0;
}