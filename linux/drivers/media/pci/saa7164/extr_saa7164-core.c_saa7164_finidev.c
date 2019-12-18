#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct saa7164_dev {size_t board; int msi; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  devlist; int /*<<< orphan*/ * i2c_bus; TYPE_1__* ports; scalar_t__ firmwareloaded; int /*<<< orphan*/ * kthread; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {scalar_t__ porta; scalar_t__ portb; scalar_t__ portc; scalar_t__ portd; scalar_t__ porte; scalar_t__ portf; } ;
struct TYPE_6__ {int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  read_interval; int /*<<< orphan*/  irq_svc_interval; int /*<<< orphan*/  svc_interval; int /*<<< orphan*/  irq_interval; } ;

/* Variables and functions */
 size_t SAA7164_BOARD_UNKNOWN ; 
 scalar_t__ SAA7164_MPEG_DVB ; 
 scalar_t__ SAA7164_MPEG_ENCODER ; 
 scalar_t__ SAA7164_MPEG_VBI ; 
 size_t SAA7164_PORT_ENC1 ; 
 size_t SAA7164_PORT_ENC2 ; 
 size_t SAA7164_PORT_TS1 ; 
 size_t SAA7164_PORT_TS2 ; 
 size_t SAA7164_PORT_VBI1 ; 
 size_t SAA7164_PORT_VBI2 ; 
 int /*<<< orphan*/  devlist ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct saa7164_dev*) ; 
 scalar_t__ fw_debug ; 
 int /*<<< orphan*/  kfree (struct saa7164_dev*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct saa7164_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  saa7164_api_set_debug (struct saa7164_dev*,int) ; 
 TYPE_5__* saa7164_boards ; 
 int /*<<< orphan*/  saa7164_dev_unregister (struct saa7164_dev*) ; 
 int /*<<< orphan*/  saa7164_dvb_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  saa7164_encoder_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  saa7164_histogram_print (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7164_i2c_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7164_shutdown (struct saa7164_dev*) ; 
 int /*<<< orphan*/  saa7164_vbi_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void saa7164_finidev(struct pci_dev *pci_dev)
{
	struct saa7164_dev *dev = pci_get_drvdata(pci_dev);

	if (dev->board != SAA7164_BOARD_UNKNOWN) {
		if (fw_debug && dev->kthread) {
			kthread_stop(dev->kthread);
			dev->kthread = NULL;
		}
		if (dev->firmwareloaded)
			saa7164_api_set_debug(dev, 0x00);
	}

	saa7164_histogram_print(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].irq_interval);
	saa7164_histogram_print(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].svc_interval);
	saa7164_histogram_print(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].irq_svc_interval);
	saa7164_histogram_print(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].read_interval);
	saa7164_histogram_print(&dev->ports[SAA7164_PORT_ENC1],
		&dev->ports[SAA7164_PORT_ENC1].poll_interval);
	saa7164_histogram_print(&dev->ports[SAA7164_PORT_VBI1],
		&dev->ports[SAA7164_PORT_VBI1].read_interval);
	saa7164_histogram_print(&dev->ports[SAA7164_PORT_VBI2],
		&dev->ports[SAA7164_PORT_VBI2].poll_interval);

	saa7164_shutdown(dev);

	if (saa7164_boards[dev->board].porta == SAA7164_MPEG_DVB)
		saa7164_dvb_unregister(&dev->ports[SAA7164_PORT_TS1]);

	if (saa7164_boards[dev->board].portb == SAA7164_MPEG_DVB)
		saa7164_dvb_unregister(&dev->ports[SAA7164_PORT_TS2]);

	if (saa7164_boards[dev->board].portc == SAA7164_MPEG_ENCODER)
		saa7164_encoder_unregister(&dev->ports[SAA7164_PORT_ENC1]);

	if (saa7164_boards[dev->board].portd == SAA7164_MPEG_ENCODER)
		saa7164_encoder_unregister(&dev->ports[SAA7164_PORT_ENC2]);

	if (saa7164_boards[dev->board].porte == SAA7164_MPEG_VBI)
		saa7164_vbi_unregister(&dev->ports[SAA7164_PORT_VBI1]);

	if (saa7164_boards[dev->board].portf == SAA7164_MPEG_VBI)
		saa7164_vbi_unregister(&dev->ports[SAA7164_PORT_VBI2]);

	saa7164_i2c_unregister(&dev->i2c_bus[0]);
	saa7164_i2c_unregister(&dev->i2c_bus[1]);
	saa7164_i2c_unregister(&dev->i2c_bus[2]);

	/* unregister stuff */
	free_irq(pci_dev->irq, dev);

	if (dev->msi) {
		pci_disable_msi(pci_dev);
		dev->msi = false;
	}

	pci_disable_device(pci_dev);

	mutex_lock(&devlist);
	list_del(&dev->devlist);
	mutex_unlock(&devlist);

	saa7164_dev_unregister(dev);
	v4l2_device_unregister(&dev->v4l2_dev);
	kfree(dev);
}