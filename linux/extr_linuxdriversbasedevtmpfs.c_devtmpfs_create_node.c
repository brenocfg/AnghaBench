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
struct req {int mode; int err; int /*<<< orphan*/  done; struct req* next; struct device* dev; int /*<<< orphan*/  name; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int S_IFBLK ; 
 int S_IFCHR ; 
 int /*<<< orphan*/  device_get_devnode (struct device*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ is_blockdev (struct device*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int /*<<< orphan*/  req_lock ; 
 struct req* requests ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

int devtmpfs_create_node(struct device *dev)
{
	const char *tmp = NULL;
	struct req req;

	if (!thread)
		return 0;

	req.mode = 0;
	req.uid = GLOBAL_ROOT_UID;
	req.gid = GLOBAL_ROOT_GID;
	req.name = device_get_devnode(dev, &req.mode, &req.uid, &req.gid, &tmp);
	if (!req.name)
		return -ENOMEM;

	if (req.mode == 0)
		req.mode = 0600;
	if (is_blockdev(dev))
		req.mode |= S_IFBLK;
	else
		req.mode |= S_IFCHR;

	req.dev = dev;

	init_completion(&req.done);

	spin_lock(&req_lock);
	req.next = requests;
	requests = &req;
	spin_unlock(&req_lock);

	wake_up_process(thread);
	wait_for_completion(&req.done);

	kfree(tmp);

	return req.err;
}