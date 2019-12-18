#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct miscdevice {TYPE_2__ notifier; int /*<<< orphan*/  wait_event; int /*<<< orphan*/  events; struct cros_ec_dev* ec_dev; int /*<<< orphan*/  parent; } ;
struct inode {int dummy; } ;
struct file {struct miscdevice* private_data; } ;
struct cros_ec_dev {int /*<<< orphan*/  dev; TYPE_1__* ec_dev; } ;
struct chardev_priv {TYPE_2__ notifier; int /*<<< orphan*/  wait_event; int /*<<< orphan*/  events; struct cros_ec_dev* ec_dev; int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_notifier; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  cros_ec_chardev_mkbp_event ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct miscdevice*) ; 
 struct miscdevice* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int cros_ec_chardev_open(struct inode *inode, struct file *filp)
{
	struct miscdevice *mdev = filp->private_data;
	struct cros_ec_dev *ec_dev = dev_get_drvdata(mdev->parent);
	struct chardev_priv *priv;
	int ret;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->ec_dev = ec_dev;
	filp->private_data = priv;
	INIT_LIST_HEAD(&priv->events);
	init_waitqueue_head(&priv->wait_event);
	nonseekable_open(inode, filp);

	priv->notifier.notifier_call = cros_ec_chardev_mkbp_event;
	ret = blocking_notifier_chain_register(&ec_dev->ec_dev->event_notifier,
					       &priv->notifier);
	if (ret) {
		dev_err(ec_dev->dev, "failed to register event notifier\n");
		kfree(priv);
	}

	return ret;
}