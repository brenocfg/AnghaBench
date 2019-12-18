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
struct v4l2_subdev {int dummy; } ;
struct v4l2_device {int dummy; } ;
struct pci_dev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cobalt {int /*<<< orphan*/  irq_work_queues; int /*<<< orphan*/  pci_dev; TYPE_1__* streams; } ;
struct TYPE_2__ {struct v4l2_subdev* sd; } ;

/* Variables and functions */
 int COBALT_NUM_ADAPTERS ; 
 int /*<<< orphan*/  COBALT_SYS_CTRL_HSMA_TX_ENABLE_BIT ; 
 int /*<<< orphan*/  cobalt_flash_remove (struct cobalt*) ; 
 int /*<<< orphan*/  cobalt_free_msi (struct cobalt*,struct pci_dev*) ; 
 int /*<<< orphan*/  cobalt_i2c_exit (struct cobalt*) ; 
 int /*<<< orphan*/  cobalt_info (char*) ; 
 int /*<<< orphan*/  cobalt_nodes_unregister (struct cobalt*) ; 
 int /*<<< orphan*/  cobalt_pci_iounmap (struct cobalt*,struct pci_dev*) ; 
 int /*<<< orphan*/  cobalt_s_bit_sysctrl (struct cobalt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cobalt_set_interrupt (struct cobalt*,int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct cobalt*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 struct v4l2_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 struct cobalt* to_cobalt (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void cobalt_remove(struct pci_dev *pci_dev)
{
	struct v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	struct cobalt *cobalt = to_cobalt(v4l2_dev);
	int i;

	cobalt_flash_remove(cobalt);
	cobalt_set_interrupt(cobalt, false);
	flush_workqueue(cobalt->irq_work_queues);
	cobalt_nodes_unregister(cobalt);
	for (i = 0; i < COBALT_NUM_ADAPTERS; i++) {
		struct v4l2_subdev *sd = cobalt->streams[i].sd;
		struct i2c_client *client;

		if (sd == NULL)
			continue;
		client = v4l2_get_subdevdata(sd);
		v4l2_device_unregister_subdev(sd);
		i2c_unregister_device(client);
	}
	cobalt_i2c_exit(cobalt);
	cobalt_free_msi(cobalt, pci_dev);
	cobalt_s_bit_sysctrl(cobalt, COBALT_SYS_CTRL_HSMA_TX_ENABLE_BIT, 0);
	cobalt_pci_iounmap(cobalt, pci_dev);
	pci_release_regions(cobalt->pci_dev);
	pci_disable_device(cobalt->pci_dev);
	destroy_workqueue(cobalt->irq_work_queues);

	cobalt_info("removed cobalt card\n");

	v4l2_device_unregister(v4l2_dev);
	kfree(cobalt);
}