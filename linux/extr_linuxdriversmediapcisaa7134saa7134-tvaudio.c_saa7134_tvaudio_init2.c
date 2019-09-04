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
struct TYPE_3__ {int /*<<< orphan*/ * thread; scalar_t__ scan2; scalar_t__ scan1; } ;
struct saa7134_dev {int /*<<< orphan*/  name; TYPE_1__ thread; TYPE_2__* pci; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
#define  PCI_DEVICE_ID_PHILIPS_SAA7133 130 
#define  PCI_DEVICE_ID_PHILIPS_SAA7134 129 
#define  PCI_DEVICE_ID_PHILIPS_SAA7135 128 
 int /*<<< orphan*/ * kthread_run (int (*) (void*),struct saa7134_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7134_enable_i2s (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_init (struct saa7134_dev*) ; 
 int tvaudio_thread (void*) ; 
 int tvaudio_thread_ddep (void*) ; 

int saa7134_tvaudio_init2(struct saa7134_dev *dev)
{
	int (*my_thread)(void *data) = NULL;

	switch (dev->pci->device) {
	case PCI_DEVICE_ID_PHILIPS_SAA7134:
		my_thread = tvaudio_thread;
		break;
	case PCI_DEVICE_ID_PHILIPS_SAA7133:
	case PCI_DEVICE_ID_PHILIPS_SAA7135:
		my_thread = tvaudio_thread_ddep;
		break;
	}

	dev->thread.thread = NULL;
	dev->thread.scan1 = dev->thread.scan2 = 0;
	if (my_thread) {
		saa7134_tvaudio_init(dev);
		/* start tvaudio thread */
		dev->thread.thread = kthread_run(my_thread, dev, "%s", dev->name);
		if (IS_ERR(dev->thread.thread)) {
			pr_warn("%s: kernel_thread() failed\n",
			       dev->name);
			/* XXX: missing error handling here */
		}
	}

	saa7134_enable_i2s(dev);
	return 0;
}