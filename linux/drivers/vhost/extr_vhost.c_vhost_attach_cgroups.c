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
struct vhost_dev {int dummy; } ;
struct vhost_attach_cgroups_struct {int ret; int /*<<< orphan*/  work; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  vhost_attach_cgroups_work ; 
 int /*<<< orphan*/  vhost_work_flush (struct vhost_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_work_queue (struct vhost_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vhost_attach_cgroups(struct vhost_dev *dev)
{
	struct vhost_attach_cgroups_struct attach;

	attach.owner = current;
	vhost_work_init(&attach.work, vhost_attach_cgroups_work);
	vhost_work_queue(dev, &attach.work);
	vhost_work_flush(dev, &attach.work);
	return attach.ret;
}