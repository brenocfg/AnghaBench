#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cnt_enb; int cnt_val; } ;
union cvmx_iob_n2c_l2c_pri_cnt {scalar_t__ u64; TYPE_2__ s; } ;
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int uses_new_polling; TYPE_3__ self; scalar_t__ hcd_priv; } ;
struct resource {int start; } ;
struct device {TYPE_1__* of_node; } ;
struct platform_device {struct device dev; } ;
struct octeon_hcd {int init_flags; int index; int idle_hardware_channels; int /*<<< orphan*/ * active_pipes; int /*<<< orphan*/  idle_pipes; int /*<<< orphan*/  lock; } ;
struct device_node {int dummy; } ;
typedef  int irq_hw_number_t ;
struct TYPE_4__ {struct device_node* parent; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CVMX_IOB_N2C_L2C_PRI_CNT ; 
 int CVMX_USB_INITIALIZE_FLAGS_CLOCK_12MHZ ; 
 int CVMX_USB_INITIALIZE_FLAGS_CLOCK_24MHZ ; 
 int CVMX_USB_INITIALIZE_FLAGS_CLOCK_48MHZ ; 
 int CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_GND ; 
 int CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_XI ; 
 int CVMX_USB_INITIALIZE_FLAGS_NO_DMA ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  OCTEON_CN31XX ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_usb_initialize (struct device*,struct octeon_hcd*) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int irq_create_mapping (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  octeon_hc_driver ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int octeon_usb_probe(struct platform_device *pdev)
{
	int status;
	int initialize_flags;
	int usb_num;
	struct resource *res_mem;
	struct device_node *usbn_node;
	int irq = platform_get_irq(pdev, 0);
	struct device *dev = &pdev->dev;
	struct octeon_hcd *usb;
	struct usb_hcd *hcd;
	u32 clock_rate = 48000000;
	bool is_crystal_clock = false;
	const char *clock_type;
	int i;

	if (!dev->of_node) {
		dev_err(dev, "Error: empty of_node\n");
		return -ENXIO;
	}
	usbn_node = dev->of_node->parent;

	i = of_property_read_u32(usbn_node,
				 "clock-frequency", &clock_rate);
	if (i)
		i = of_property_read_u32(usbn_node,
					 "refclk-frequency", &clock_rate);
	if (i) {
		dev_err(dev, "No USBN \"clock-frequency\"\n");
		return -ENXIO;
	}
	switch (clock_rate) {
	case 12000000:
		initialize_flags = CVMX_USB_INITIALIZE_FLAGS_CLOCK_12MHZ;
		break;
	case 24000000:
		initialize_flags = CVMX_USB_INITIALIZE_FLAGS_CLOCK_24MHZ;
		break;
	case 48000000:
		initialize_flags = CVMX_USB_INITIALIZE_FLAGS_CLOCK_48MHZ;
		break;
	default:
		dev_err(dev, "Illegal USBN \"clock-frequency\" %u\n",
			clock_rate);
		return -ENXIO;
	}

	i = of_property_read_string(usbn_node,
				    "cavium,refclk-type", &clock_type);
	if (i)
		i = of_property_read_string(usbn_node,
					    "refclk-type", &clock_type);

	if (!i && strcmp("crystal", clock_type) == 0)
		is_crystal_clock = true;

	if (is_crystal_clock)
		initialize_flags |= CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_XI;
	else
		initialize_flags |= CVMX_USB_INITIALIZE_FLAGS_CLOCK_XO_GND;

	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res_mem) {
		dev_err(dev, "found no memory resource\n");
		return -ENXIO;
	}
	usb_num = (res_mem->start >> 44) & 1;

	if (irq < 0) {
		/* Defective device tree, but we know how to fix it. */
		irq_hw_number_t hwirq = usb_num ? (1 << 6) + 17 : 56;

		irq = irq_create_mapping(NULL, hwirq);
	}

	/*
	 * Set the DMA mask to 64bits so we get buffers already translated for
	 * DMA.
	 */
	i = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(64));
	if (i)
		return i;

	/*
	 * Only cn52XX and cn56XX have DWC_OTG USB hardware and the
	 * IOB priority registers.  Under heavy network load USB
	 * hardware can be starved by the IOB causing a crash.  Give
	 * it a priority boost if it has been waiting more than 400
	 * cycles to avoid this situation.
	 *
	 * Testing indicates that a cnt_val of 8192 is not sufficient,
	 * but no failures are seen with 4096.  We choose a value of
	 * 400 to give a safety factor of 10.
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN52XX) || OCTEON_IS_MODEL(OCTEON_CN56XX)) {
		union cvmx_iob_n2c_l2c_pri_cnt pri_cnt;

		pri_cnt.u64 = 0;
		pri_cnt.s.cnt_enb = 1;
		pri_cnt.s.cnt_val = 400;
		cvmx_write_csr(CVMX_IOB_N2C_L2C_PRI_CNT, pri_cnt.u64);
	}

	hcd = usb_create_hcd(&octeon_hc_driver, dev, dev_name(dev));
	if (!hcd) {
		dev_dbg(dev, "Failed to allocate memory for HCD\n");
		return -1;
	}
	hcd->uses_new_polling = 1;
	usb = (struct octeon_hcd *)hcd->hcd_priv;

	spin_lock_init(&usb->lock);

	usb->init_flags = initialize_flags;

	/* Initialize the USB state structure */
	usb->index = usb_num;
	INIT_LIST_HEAD(&usb->idle_pipes);
	for (i = 0; i < ARRAY_SIZE(usb->active_pipes); i++)
		INIT_LIST_HEAD(&usb->active_pipes[i]);

	/* Due to an errata, CN31XX doesn't support DMA */
	if (OCTEON_IS_MODEL(OCTEON_CN31XX)) {
		usb->init_flags |= CVMX_USB_INITIALIZE_FLAGS_NO_DMA;
		/* Only use one channel with non DMA */
		usb->idle_hardware_channels = 0x1;
	} else if (OCTEON_IS_MODEL(OCTEON_CN5XXX)) {
		/* CN5XXX have an errata with channel 3 */
		usb->idle_hardware_channels = 0xf7;
	} else {
		usb->idle_hardware_channels = 0xff;
	}

	status = cvmx_usb_initialize(dev, usb);
	if (status) {
		dev_dbg(dev, "USB initialization failed with %d\n", status);
		usb_put_hcd(hcd);
		return -1;
	}

	status = usb_add_hcd(hcd, irq, 0);
	if (status) {
		dev_dbg(dev, "USB add HCD failed with %d\n", status);
		usb_put_hcd(hcd);
		return -1;
	}
	device_wakeup_enable(hcd->self.controller);

	dev_info(dev, "Registered HCD for port %d on irq %d\n", usb_num, irq);

	return 0;
}