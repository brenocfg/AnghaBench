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
struct resource {int start; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; struct device* parent; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct musb_hdrc_platform_data {int power; int /*<<< orphan*/  mode; int /*<<< orphan*/ * platform_ops; struct musb_hdrc_config* config; } ;
struct musb_hdrc_config {int num_eps; int ram_bits; int host_port_deassert_reset_at_resume; int multipoint; int maximum_speed; } ;
struct dsps_glue {struct platform_device* musb; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  resources ;
typedef  int /*<<< orphan*/  pdata ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct resource*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
#define  USB_SPEED_FULL 130 
 int USB_SPEED_HIGH ; 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_SUPER 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  device_set_of_node_from_dev (struct device*,struct device*) ; 
 struct musb_hdrc_config* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsps_ops ; 
 int get_int_prop (struct device_node*,char*) ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  musb_dmamask ; 
 int /*<<< orphan*/  musb_get_mode (struct device*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct musb_hdrc_platform_data*,int) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int /*<<< orphan*/ ) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int usb_get_maximum_speed (struct device*) ; 

__attribute__((used)) static int dsps_create_musb_pdev(struct dsps_glue *glue,
		struct platform_device *parent)
{
	struct musb_hdrc_platform_data pdata;
	struct resource	resources[2];
	struct resource	*res;
	struct device *dev = &parent->dev;
	struct musb_hdrc_config	*config;
	struct platform_device *musb;
	struct device_node *dn = parent->dev.of_node;
	int ret, val;

	memset(resources, 0, sizeof(resources));
	res = platform_get_resource_byname(parent, IORESOURCE_MEM, "mc");
	if (!res) {
		dev_err(dev, "failed to get memory.\n");
		return -EINVAL;
	}
	resources[0] = *res;

	res = platform_get_resource_byname(parent, IORESOURCE_IRQ, "mc");
	if (!res) {
		dev_err(dev, "failed to get irq.\n");
		return -EINVAL;
	}
	resources[1] = *res;

	/* allocate the child platform device */
	musb = platform_device_alloc("musb-hdrc",
			(resources[0].start & 0xFFF) == 0x400 ? 0 : 1);
	if (!musb) {
		dev_err(dev, "failed to allocate musb device\n");
		return -ENOMEM;
	}

	musb->dev.parent		= dev;
	musb->dev.dma_mask		= &musb_dmamask;
	musb->dev.coherent_dma_mask	= musb_dmamask;
	device_set_of_node_from_dev(&musb->dev, &parent->dev);

	glue->musb = musb;

	ret = platform_device_add_resources(musb, resources,
			ARRAY_SIZE(resources));
	if (ret) {
		dev_err(dev, "failed to add resources\n");
		goto err;
	}

	config = devm_kzalloc(&parent->dev, sizeof(*config), GFP_KERNEL);
	if (!config) {
		ret = -ENOMEM;
		goto err;
	}
	pdata.config = config;
	pdata.platform_ops = &dsps_ops;

	config->num_eps = get_int_prop(dn, "mentor,num-eps");
	config->ram_bits = get_int_prop(dn, "mentor,ram-bits");
	config->host_port_deassert_reset_at_resume = 1;
	pdata.mode = musb_get_mode(dev);
	/* DT keeps this entry in mA, musb expects it as per USB spec */
	pdata.power = get_int_prop(dn, "mentor,power") / 2;

	ret = of_property_read_u32(dn, "mentor,multipoint", &val);
	if (!ret && val)
		config->multipoint = true;

	config->maximum_speed = usb_get_maximum_speed(&parent->dev);
	switch (config->maximum_speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
		break;
	case USB_SPEED_SUPER:
		dev_warn(dev, "ignore incorrect maximum_speed "
				"(super-speed) setting in dts");
		/* fall through */
	default:
		config->maximum_speed = USB_SPEED_HIGH;
	}

	ret = platform_device_add_data(musb, &pdata, sizeof(pdata));
	if (ret) {
		dev_err(dev, "failed to add platform_data\n");
		goto err;
	}

	ret = platform_device_add(musb);
	if (ret) {
		dev_err(dev, "failed to register musb device\n");
		goto err;
	}
	return 0;

err:
	platform_device_put(musb);
	return ret;
}