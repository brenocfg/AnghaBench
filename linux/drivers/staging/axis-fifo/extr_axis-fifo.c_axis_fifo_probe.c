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
struct resource {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct platform_device {struct device dev; } ;
struct axis_fifo {unsigned int rx_fifo_depth; unsigned int tx_fifo_depth; unsigned int has_rx_fifo; unsigned int has_tx_fifo; struct resource* mem; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  devt; int /*<<< orphan*/  char_device; struct device* dt_device; struct device* device; int /*<<< orphan*/  write_queue_lock; int /*<<< orphan*/  read_queue_lock; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  read_queue; } ;
typedef  int /*<<< orphan*/  device_name ;

/* Variables and functions */
 char* DRIVER_NAME ; 
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/ * MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MINOR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  axis_fifo_attrs_group ; 
 int /*<<< orphan*/  axis_fifo_driver_class ; 
 int /*<<< orphan*/  axis_fifo_irq ; 
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct axis_fifo*) ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axis_fifo* devm_kmalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fops ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct axis_fifo*) ; 
 int get_dts_property (struct axis_fifo*,char*,unsigned int*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct axis_fifo*) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_ip_core (struct axis_fifo*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axis_fifo_probe(struct platform_device *pdev)
{
	struct resource *r_irq; /* interrupt resources */
	struct resource *r_mem; /* IO mem resources */
	struct device *dev = &pdev->dev; /* OS device (from device tree) */
	struct axis_fifo *fifo = NULL;

	char device_name[32];

	int rc = 0; /* error return value */

	/* IP properties from device tree */
	unsigned int rxd_tdata_width;
	unsigned int txc_tdata_width;
	unsigned int txd_tdata_width;
	unsigned int tdest_width;
	unsigned int tid_width;
	unsigned int tuser_width;
	unsigned int data_interface_type;
	unsigned int has_tdest;
	unsigned int has_tid;
	unsigned int has_tkeep;
	unsigned int has_tstrb;
	unsigned int has_tuser;
	unsigned int rx_fifo_depth;
	unsigned int rx_programmable_empty_threshold;
	unsigned int rx_programmable_full_threshold;
	unsigned int axi_id_width;
	unsigned int axi4_data_width;
	unsigned int select_xpm;
	unsigned int tx_fifo_depth;
	unsigned int tx_programmable_empty_threshold;
	unsigned int tx_programmable_full_threshold;
	unsigned int use_rx_cut_through;
	unsigned int use_rx_data;
	unsigned int use_tx_control;
	unsigned int use_tx_cut_through;
	unsigned int use_tx_data;

	/* ----------------------------
	 *     init wrapper device
	 * ----------------------------
	 */

	/* allocate device wrapper memory */
	fifo = devm_kmalloc(dev, sizeof(*fifo), GFP_KERNEL);
	if (!fifo)
		return -ENOMEM;

	dev_set_drvdata(dev, fifo);
	fifo->dt_device = dev;

	init_waitqueue_head(&fifo->read_queue);
	init_waitqueue_head(&fifo->write_queue);

	spin_lock_init(&fifo->read_queue_lock);
	spin_lock_init(&fifo->write_queue_lock);

	/* ----------------------------
	 *   init device memory space
	 * ----------------------------
	 */

	/* get iospace for the device */
	r_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r_mem) {
		dev_err(fifo->dt_device, "invalid address\n");
		rc = -ENODEV;
		goto err_initial;
	}

	fifo->mem = r_mem;

	/* request physical memory */
	if (!request_mem_region(fifo->mem->start, resource_size(fifo->mem),
				DRIVER_NAME)) {
		dev_err(fifo->dt_device,
			"couldn't lock memory region at 0x%pa\n",
			&fifo->mem->start);
		rc = -EBUSY;
		goto err_initial;
	}
	dev_dbg(fifo->dt_device, "got memory location [0x%pa - 0x%pa]\n",
		&fifo->mem->start, &fifo->mem->end);

	/* map physical memory to kernel virtual address space */
	fifo->base_addr = ioremap(fifo->mem->start, resource_size(fifo->mem));
	if (!fifo->base_addr) {
		dev_err(fifo->dt_device, "couldn't map physical memory\n");
		rc = -ENOMEM;
		goto err_mem;
	}
	dev_dbg(fifo->dt_device, "remapped memory to 0x%p\n", fifo->base_addr);

	/* create unique device name */
	snprintf(device_name, sizeof(device_name), "%s_%pa",
		 DRIVER_NAME, &fifo->mem->start);

	dev_dbg(fifo->dt_device, "device name [%s]\n", device_name);

	/* ----------------------------
	 *          init IP
	 * ----------------------------
	 */

	/* retrieve device tree properties */
	rc = get_dts_property(fifo, "xlnx,axi-str-rxd-tdata-width",
			      &rxd_tdata_width);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,axi-str-txc-tdata-width",
			      &txc_tdata_width);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,axi-str-txd-tdata-width",
			      &txd_tdata_width);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,axis-tdest-width", &tdest_width);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,axis-tid-width", &tid_width);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,axis-tuser-width", &tuser_width);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,data-interface-type",
			      &data_interface_type);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,has-axis-tdest", &has_tdest);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,has-axis-tid", &has_tid);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,has-axis-tkeep", &has_tkeep);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,has-axis-tstrb", &has_tstrb);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,has-axis-tuser", &has_tuser);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,rx-fifo-depth", &rx_fifo_depth);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,rx-fifo-pe-threshold",
			      &rx_programmable_empty_threshold);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,rx-fifo-pf-threshold",
			      &rx_programmable_full_threshold);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,s-axi-id-width", &axi_id_width);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,s-axi4-data-width", &axi4_data_width);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,select-xpm", &select_xpm);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,tx-fifo-depth", &tx_fifo_depth);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,tx-fifo-pe-threshold",
			      &tx_programmable_empty_threshold);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,tx-fifo-pf-threshold",
			      &tx_programmable_full_threshold);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,use-rx-cut-through",
			      &use_rx_cut_through);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,use-rx-data", &use_rx_data);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,use-tx-ctrl", &use_tx_control);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,use-tx-cut-through",
			      &use_tx_cut_through);
	if (rc)
		goto err_unmap;
	rc = get_dts_property(fifo, "xlnx,use-tx-data", &use_tx_data);
	if (rc)
		goto err_unmap;

	/* check validity of device tree properties */
	if (rxd_tdata_width != 32) {
		dev_err(fifo->dt_device,
			"rxd_tdata_width width [%u] unsupported\n",
			rxd_tdata_width);
		rc = -EIO;
		goto err_unmap;
	}
	if (txd_tdata_width != 32) {
		dev_err(fifo->dt_device,
			"txd_tdata_width width [%u] unsupported\n",
			txd_tdata_width);
		rc = -EIO;
		goto err_unmap;
	}
	if (has_tdest) {
		dev_err(fifo->dt_device, "tdest not supported\n");
		rc = -EIO;
		goto err_unmap;
	}
	if (has_tid) {
		dev_err(fifo->dt_device, "tid not supported\n");
		rc = -EIO;
		goto err_unmap;
	}
	if (has_tkeep) {
		dev_err(fifo->dt_device, "tkeep not supported\n");
		rc = -EIO;
		goto err_unmap;
	}
	if (has_tstrb) {
		dev_err(fifo->dt_device, "tstrb not supported\n");
		rc = -EIO;
		goto err_unmap;
	}
	if (has_tuser) {
		dev_err(fifo->dt_device, "tuser not supported\n");
		rc = -EIO;
		goto err_unmap;
	}
	if (use_rx_cut_through) {
		dev_err(fifo->dt_device, "rx cut-through not supported\n");
		rc = -EIO;
		goto err_unmap;
	}
	if (use_tx_cut_through) {
		dev_err(fifo->dt_device, "tx cut-through not supported\n");
		rc = -EIO;
		goto err_unmap;
	}
	if (use_tx_control) {
		dev_err(fifo->dt_device, "tx control not supported\n");
		rc = -EIO;
		goto err_unmap;
	}

	/* TODO
	 * these exist in the device tree but it's unclear what they do
	 * - select-xpm
	 * - data-interface-type
	 */

	/* set device wrapper properties based on IP config */
	fifo->rx_fifo_depth = rx_fifo_depth;
	/* IP sets TDFV to fifo depth - 4 so we will do the same */
	fifo->tx_fifo_depth = tx_fifo_depth - 4;
	fifo->has_rx_fifo = use_rx_data;
	fifo->has_tx_fifo = use_tx_data;

	reset_ip_core(fifo);

	/* ----------------------------
	 *    init device interrupts
	 * ----------------------------
	 */

	/* get IRQ resource */
	r_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!r_irq) {
		dev_err(fifo->dt_device, "no IRQ found for 0x%pa\n",
			&fifo->mem->start);
		rc = -EIO;
		goto err_unmap;
	}

	/* request IRQ */
	fifo->irq = r_irq->start;
	rc = request_irq(fifo->irq, &axis_fifo_irq, 0, DRIVER_NAME, fifo);
	if (rc) {
		dev_err(fifo->dt_device, "couldn't allocate interrupt %i\n",
			fifo->irq);
		goto err_unmap;
	}

	/* ----------------------------
	 *      init char device
	 * ----------------------------
	 */

	/* allocate device number */
	rc = alloc_chrdev_region(&fifo->devt, 0, 1, DRIVER_NAME);
	if (rc < 0)
		goto err_irq;
	dev_dbg(fifo->dt_device, "allocated device number major %i minor %i\n",
		MAJOR(fifo->devt), MINOR(fifo->devt));

	/* create driver file */
	fifo->device = device_create(axis_fifo_driver_class, NULL, fifo->devt,
				     NULL, device_name);
	if (IS_ERR(fifo->device)) {
		dev_err(fifo->dt_device,
			"couldn't create driver file\n");
		rc = PTR_ERR(fifo->device);
		goto err_chrdev_region;
	}
	dev_set_drvdata(fifo->device, fifo);

	/* create character device */
	cdev_init(&fifo->char_device, &fops);
	rc = cdev_add(&fifo->char_device, fifo->devt, 1);
	if (rc < 0) {
		dev_err(fifo->dt_device, "couldn't create character device\n");
		goto err_dev;
	}

	/* create sysfs entries */
	rc = sysfs_create_group(&fifo->device->kobj, &axis_fifo_attrs_group);
	if (rc < 0) {
		dev_err(fifo->dt_device, "couldn't register sysfs group\n");
		goto err_cdev;
	}

	dev_info(fifo->dt_device, "axis-fifo created at %pa mapped to 0x%pa, irq=%i, major=%i, minor=%i\n",
		 &fifo->mem->start, &fifo->base_addr, fifo->irq,
		 MAJOR(fifo->devt), MINOR(fifo->devt));

	return 0;

err_cdev:
	cdev_del(&fifo->char_device);
err_dev:
	device_destroy(axis_fifo_driver_class, fifo->devt);
err_chrdev_region:
	unregister_chrdev_region(fifo->devt, 1);
err_irq:
	free_irq(fifo->irq, fifo);
err_unmap:
	iounmap(fifo->base_addr);
err_mem:
	release_mem_region(fifo->mem->start, resource_size(fifo->mem));
err_initial:
	dev_set_drvdata(dev, NULL);
	return rc;
}