#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_9__ {int ngpio; } ;
struct hlwd_gpio {TYPE_4__ gpioc; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGPIOF_BIG_ENDIAN_BYTE_ORDER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HW_GPIOB_DIR ; 
 scalar_t__ HW_GPIOB_IN ; 
 scalar_t__ HW_GPIOB_OUT ; 
 scalar_t__ HW_GPIO_OWNER ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int bgpio_init (TYPE_4__*,TYPE_1__*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int devm_gpiochip_add_data (TYPE_1__*,TYPE_4__*,struct hlwd_gpio*) ; 
 scalar_t__ devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct hlwd_gpio* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hlwd_gpio_probe(struct platform_device *pdev)
{
	struct hlwd_gpio *hlwd;
	struct resource *regs_resource;
	u32 ngpios;
	int res;

	hlwd = devm_kzalloc(&pdev->dev, sizeof(*hlwd), GFP_KERNEL);
	if (!hlwd)
		return -ENOMEM;

	regs_resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hlwd->regs = devm_ioremap_resource(&pdev->dev, regs_resource);
	if (IS_ERR(hlwd->regs))
		return PTR_ERR(hlwd->regs);

	/*
	 * Claim all GPIOs using the OWNER register. This will not work on
	 * systems where the AHBPROT memory firewall hasn't been configured to
	 * permit PPC access to HW_GPIO_*.
	 *
	 * Note that this has to happen before bgpio_init reads the
	 * HW_GPIOB_OUT and HW_GPIOB_DIR, because otherwise it reads the wrong
	 * values.
	 */
	iowrite32be(0xffffffff, hlwd->regs + HW_GPIO_OWNER);

	res = bgpio_init(&hlwd->gpioc, &pdev->dev, 4,
			hlwd->regs + HW_GPIOB_IN, hlwd->regs + HW_GPIOB_OUT,
			NULL, hlwd->regs + HW_GPIOB_DIR, NULL,
			BGPIOF_BIG_ENDIAN_BYTE_ORDER);
	if (res < 0) {
		dev_warn(&pdev->dev, "bgpio_init failed: %d\n", res);
		return res;
	}

	res = of_property_read_u32(pdev->dev.of_node, "ngpios", &ngpios);
	if (res)
		ngpios = 32;
	hlwd->gpioc.ngpio = ngpios;

	return devm_gpiochip_add_data(&pdev->dev, &hlwd->gpioc, hlwd);
}