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
struct TYPE_2__ {int bit_rate; } ;
struct pi433_instance {TYPE_1__ tx_cfg; struct pi433_device* device; } ;
struct pi433_device {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct pi433_instance* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pi433_device* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 struct pi433_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pi433_idr ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_open (struct inode*,struct file*) ; 

__attribute__((used)) static int pi433_open(struct inode *inode, struct file *filp)
{
	struct pi433_device	*device;
	struct pi433_instance	*instance;

	mutex_lock(&minor_lock);
	device = idr_find(&pi433_idr, iminor(inode));
	mutex_unlock(&minor_lock);
	if (!device) {
		pr_debug("device: minor %d unknown.\n", iminor(inode));
		return -ENODEV;
	}

	instance = kzalloc(sizeof(*instance), GFP_KERNEL);
	if (!instance)
		return -ENOMEM;

	/* setup instance data*/
	instance->device = device;
	instance->tx_cfg.bit_rate = 4711;
	// TODO: fill instance->tx_cfg;

	/* instance data as context */
	filp->private_data = instance;
	stream_open(inode, filp);

	return 0;
}