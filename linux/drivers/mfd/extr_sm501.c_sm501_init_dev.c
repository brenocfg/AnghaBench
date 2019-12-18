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
struct sm501_platdata {scalar_t__ gpio_i2c_nr; scalar_t__ gpio_i2c; struct sm501_initdata* init; } ;
struct sm501_initdata {int devices; } ;
struct sm501_devdata {unsigned long rev; int /*<<< orphan*/  dev; struct sm501_platdata* platdata; int /*<<< orphan*/  irq; scalar_t__ regs; int /*<<< orphan*/  devices; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  clock_lock; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ SM501_DEVICEID ; 
 unsigned long SM501_DEVICEID_IDMASK ; 
 unsigned long SM501_DEVICEID_REVMASK ; 
 unsigned long SM501_DEVICEID_SM501 ; 
 scalar_t__ SM501_DRAM_CONTROL ; 
 scalar_t__ SM501_IRQ_MASK ; 
 int SM501_USE_GPIO ; 
 int SM501_USE_UART0 ; 
 int SM501_USE_UART1 ; 
 int SM501_USE_USB_HOST ; 
 int /*<<< orphan*/  dev_attr_dbg_regs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sm501_check_clocks (struct sm501_devdata*) ; 
 int /*<<< orphan*/  sm501_dump_clk (struct sm501_devdata*) ; 
 int /*<<< orphan*/  sm501_dump_gate (struct sm501_devdata*) ; 
 int /*<<< orphan*/  sm501_gpio_isregistered (struct sm501_devdata*) ; 
 int /*<<< orphan*/  sm501_init_regs (struct sm501_devdata*,struct sm501_initdata*) ; 
 scalar_t__* sm501_mem_local ; 
 int /*<<< orphan*/  sm501_register_display (struct sm501_devdata*,scalar_t__*) ; 
 int /*<<< orphan*/  sm501_register_gpio (struct sm501_devdata*) ; 
 int /*<<< orphan*/  sm501_register_gpio_i2c (struct sm501_devdata*,struct sm501_platdata*) ; 
 int /*<<< orphan*/  sm501_register_uart (struct sm501_devdata*,int) ; 
 int /*<<< orphan*/  sm501_register_usbhost (struct sm501_devdata*,scalar_t__*) ; 
 unsigned long smc501_readl (scalar_t__) ; 
 int /*<<< orphan*/  smc501_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sm501_init_dev(struct sm501_devdata *sm)
{
	struct sm501_initdata *idata;
	struct sm501_platdata *pdata;
	resource_size_t mem_avail;
	unsigned long dramctrl;
	unsigned long devid;
	int ret;

	mutex_init(&sm->clock_lock);
	spin_lock_init(&sm->reg_lock);

	INIT_LIST_HEAD(&sm->devices);

	devid = smc501_readl(sm->regs + SM501_DEVICEID);

	if ((devid & SM501_DEVICEID_IDMASK) != SM501_DEVICEID_SM501) {
		dev_err(sm->dev, "incorrect device id %08lx\n", devid);
		return -EINVAL;
	}

	/* disable irqs */
	smc501_writel(0, sm->regs + SM501_IRQ_MASK);

	dramctrl = smc501_readl(sm->regs + SM501_DRAM_CONTROL);
	mem_avail = sm501_mem_local[(dramctrl >> 13) & 0x7];

	dev_info(sm->dev, "SM501 At %p: Version %08lx, %ld Mb, IRQ %d\n",
		 sm->regs, devid, (unsigned long)mem_avail >> 20, sm->irq);

	sm->rev = devid & SM501_DEVICEID_REVMASK;

	sm501_dump_gate(sm);

	ret = device_create_file(sm->dev, &dev_attr_dbg_regs);
	if (ret)
		dev_err(sm->dev, "failed to create debug regs file\n");

	sm501_dump_clk(sm);

	/* check to see if we have some device initialisation */

	pdata = sm->platdata;
	idata = pdata ? pdata->init : NULL;

	if (idata) {
		sm501_init_regs(sm, idata);

		if (idata->devices & SM501_USE_USB_HOST)
			sm501_register_usbhost(sm, &mem_avail);
		if (idata->devices & (SM501_USE_UART0 | SM501_USE_UART1))
			sm501_register_uart(sm, idata->devices);
		if (idata->devices & SM501_USE_GPIO)
			sm501_register_gpio(sm);
	}

	if (pdata && pdata->gpio_i2c && pdata->gpio_i2c_nr > 0) {
		if (!sm501_gpio_isregistered(sm))
			dev_err(sm->dev, "no gpio available for i2c gpio.\n");
		else
			sm501_register_gpio_i2c(sm, pdata);
	}

	ret = sm501_check_clocks(sm);
	if (ret) {
		dev_err(sm->dev, "M1X and M clocks sourced from different "
					"PLLs\n");
		return -EINVAL;
	}

	/* always create a framebuffer */
	sm501_register_display(sm, &mem_avail);

	return 0;
}