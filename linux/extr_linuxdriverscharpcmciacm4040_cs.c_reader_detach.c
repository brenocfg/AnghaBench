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
struct reader_dev {int dummy; } ;
struct pcmcia_device {struct reader_dev* priv; } ;

/* Variables and functions */
 int CM_MAX_DEV ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmx_class ; 
 struct pcmcia_device** dev_table ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct reader_dev*) ; 
 int /*<<< orphan*/  major ; 
 int /*<<< orphan*/  reader_release (struct pcmcia_device*) ; 

__attribute__((used)) static void reader_detach(struct pcmcia_device *link)
{
	struct reader_dev *dev = link->priv;
	int devno;

	/* find device */
	for (devno = 0; devno < CM_MAX_DEV; devno++) {
		if (dev_table[devno] == link)
			break;
	}
	if (devno == CM_MAX_DEV)
		return;

	reader_release(link);

	dev_table[devno] = NULL;
	kfree(dev);

	device_destroy(cmx_class, MKDEV(major, devno));

	return;
}