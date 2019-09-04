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
struct pcmcia_device {scalar_t__ open; struct cm4000_dev* priv; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct cm4000_dev {int /*<<< orphan*/  devq; } ;

/* Variables and functions */
 int CM4000_MAX_DEV ; 
 int /*<<< orphan*/  DEBUGP (int,struct cm4000_dev*,char*,...) ; 
 int ENODEV ; 
 int /*<<< orphan*/  ZERO_DEV (struct cm4000_dev*) ; 
 struct pcmcia_device** dev_table ; 
 int /*<<< orphan*/  imajor (struct inode*) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  stop_monitor (struct cm4000_dev*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmm_close(struct inode *inode, struct file *filp)
{
	struct cm4000_dev *dev;
	struct pcmcia_device *link;
	int minor = iminor(inode);

	if (minor >= CM4000_MAX_DEV)
		return -ENODEV;

	link = dev_table[minor];
	if (link == NULL)
		return -ENODEV;

	dev = link->priv;

	DEBUGP(2, dev, "-> cmm_close(maj/min=%d.%d)\n",
	       imajor(inode), minor);

	stop_monitor(dev);

	ZERO_DEV(dev);

	link->open = 0;		/* only one open per device */
	wake_up(&dev->devq);	/* socket removed? */

	DEBUGP(2, dev, "cmm_close\n");
	return 0;
}