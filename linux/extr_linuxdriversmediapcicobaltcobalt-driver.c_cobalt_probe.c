#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  notify; } ;
struct cobalt {int instance; TYPE_1__ v4l2_dev; int /*<<< orphan*/ * irq_work_queues; struct pci_dev* pci_dev; int /*<<< orphan*/  hdl_info; int /*<<< orphan*/  irq_work_queue; } ;

/* Variables and functions */
 int COBALT_SYSSTAT_HSMA_PRSNTN_MSK ; 
 int /*<<< orphan*/  COBALT_SYS_CTRL_HSMA_TX_ENABLE_BIT ; 
 int /*<<< orphan*/  COBALT_SYS_STAT_BASE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cobalt_err (char*,...) ; 
 int /*<<< orphan*/  cobalt_flash_probe (struct cobalt*) ; 
 int /*<<< orphan*/  cobalt_free_msi (struct cobalt*,struct pci_dev*) ; 
 scalar_t__ cobalt_hdl_info_get (struct cobalt*) ; 
 int /*<<< orphan*/  cobalt_i2c_exit (struct cobalt*) ; 
 int cobalt_i2c_init (struct cobalt*) ; 
 int /*<<< orphan*/  cobalt_info (char*,...) ; 
 int /*<<< orphan*/  cobalt_instance ; 
 int /*<<< orphan*/  cobalt_irq_work_handler ; 
 int cobalt_nodes_register (struct cobalt*) ; 
 int /*<<< orphan*/  cobalt_notify ; 
 int /*<<< orphan*/  cobalt_pci_iounmap (struct cobalt*,struct pci_dev*) ; 
 int cobalt_read_bar1 (struct cobalt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cobalt_s_bit_sysctrl (struct cobalt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cobalt_set_interrupt (struct cobalt*,int) ; 
 int cobalt_setup_pci (struct cobalt*,struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  cobalt_stream_struct_init (struct cobalt*) ; 
 int cobalt_subdevs_hsma_init (struct cobalt*) ; 
 int cobalt_subdevs_init (struct cobalt*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interrupt_service_routine ; 
 int /*<<< orphan*/  kfree (struct cobalt*) ; 
 struct cobalt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  v4l2_device_call_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 

__attribute__((used)) static int cobalt_probe(struct pci_dev *pci_dev,
				  const struct pci_device_id *pci_id)
{
	struct cobalt *cobalt;
	int retval = 0;
	int i;

	/* FIXME - module parameter arrays constrain max instances */
	i = atomic_inc_return(&cobalt_instance) - 1;

	cobalt = kzalloc(sizeof(struct cobalt), GFP_KERNEL);
	if (cobalt == NULL)
		return -ENOMEM;
	cobalt->pci_dev = pci_dev;
	cobalt->instance = i;

	retval = v4l2_device_register(&pci_dev->dev, &cobalt->v4l2_dev);
	if (retval) {
		pr_err("cobalt: v4l2_device_register of card %d failed\n",
				cobalt->instance);
		kfree(cobalt);
		return retval;
	}
	snprintf(cobalt->v4l2_dev.name, sizeof(cobalt->v4l2_dev.name),
		 "cobalt-%d", cobalt->instance);
	cobalt->v4l2_dev.notify = cobalt_notify;
	cobalt_info("Initializing card %d\n", cobalt->instance);

	cobalt->irq_work_queues =
		create_singlethread_workqueue(cobalt->v4l2_dev.name);
	if (cobalt->irq_work_queues == NULL) {
		cobalt_err("Could not create workqueue\n");
		retval = -ENOMEM;
		goto err;
	}

	INIT_WORK(&cobalt->irq_work_queue, cobalt_irq_work_handler);

	/* PCI Device Setup */
	retval = cobalt_setup_pci(cobalt, pci_dev, pci_id);
	if (retval != 0)
		goto err_wq;

	/* Show HDL version info */
	if (cobalt_hdl_info_get(cobalt))
		cobalt_info("Not able to read the HDL info\n");
	else
		cobalt_info("%s", cobalt->hdl_info);

	retval = cobalt_i2c_init(cobalt);
	if (retval)
		goto err_pci;

	cobalt_stream_struct_init(cobalt);

	retval = cobalt_subdevs_init(cobalt);
	if (retval)
		goto err_i2c;

	if (!(cobalt_read_bar1(cobalt, COBALT_SYS_STAT_BASE) &
			COBALT_SYSSTAT_HSMA_PRSNTN_MSK)) {
		retval = cobalt_subdevs_hsma_init(cobalt);
		if (retval)
			goto err_i2c;
	}

	retval = cobalt_nodes_register(cobalt);
	if (retval) {
		cobalt_err("Error %d registering device nodes\n", retval);
		goto err_i2c;
	}
	cobalt_set_interrupt(cobalt, true);
	v4l2_device_call_all(&cobalt->v4l2_dev, 0, core,
					interrupt_service_routine, 0, NULL);

	cobalt_info("Initialized cobalt card\n");

	cobalt_flash_probe(cobalt);

	return 0;

err_i2c:
	cobalt_i2c_exit(cobalt);
	cobalt_s_bit_sysctrl(cobalt, COBALT_SYS_CTRL_HSMA_TX_ENABLE_BIT, 0);
err_pci:
	cobalt_free_msi(cobalt, pci_dev);
	cobalt_pci_iounmap(cobalt, pci_dev);
	pci_release_regions(cobalt->pci_dev);
	pci_disable_device(cobalt->pci_dev);
err_wq:
	destroy_workqueue(cobalt->irq_work_queues);
err:
	cobalt_err("error %d on initialization\n", retval);

	v4l2_device_unregister(&cobalt->v4l2_dev);
	kfree(cobalt);
	return retval;
}