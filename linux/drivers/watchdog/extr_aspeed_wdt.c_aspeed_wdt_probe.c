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
typedef  scalar_t__ u32 ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {struct aspeed_wdt_config* data; } ;
struct device_node {int dummy; } ;
struct aspeed_wdt_config {scalar_t__ ext_pulse_width_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  bootstatus; int /*<<< orphan*/  status; int /*<<< orphan*/  timeout; struct device* parent; int /*<<< orphan*/  max_hw_heartbeat_ms; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct aspeed_wdt {int ctrl; TYPE_1__ wdd; scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 scalar_t__ WDT_ACTIVE_HIGH_MAGIC ; 
 scalar_t__ WDT_ACTIVE_LOW_MAGIC ; 
 scalar_t__ WDT_CTRL ; 
 int WDT_CTRL_1MHZ_CLK ; 
 int WDT_CTRL_BOOT_SECONDARY ; 
 int WDT_CTRL_ENABLE ; 
 int WDT_CTRL_RESET_MODE_ARM_CPU ; 
 int WDT_CTRL_RESET_MODE_FULL_CHIP ; 
 int WDT_CTRL_RESET_MODE_SOC ; 
 int WDT_CTRL_RESET_SYSTEM ; 
 int WDT_CTRL_WDT_EXT ; 
 int /*<<< orphan*/  WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  WDT_MAX_TIMEOUT_MS ; 
 scalar_t__ WDT_OPEN_DRAIN_MAGIC ; 
 scalar_t__ WDT_PUSH_PULL_MAGIC ; 
 scalar_t__ WDT_RESET_WIDTH ; 
 scalar_t__ WDT_TIMEOUT_STATUS ; 
 scalar_t__ WDT_TIMEOUT_STATUS_BOOT_SECONDARY ; 
 int /*<<< orphan*/  aspeed_wdt_info ; 
 int /*<<< orphan*/  aspeed_wdt_of_table ; 
 int /*<<< orphan*/  aspeed_wdt_ops ; 
 int /*<<< orphan*/  aspeed_wdt_start (TYPE_1__*) ; 
 int /*<<< orphan*/  bswitch_groups ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct aspeed_wdt*) ; 
 struct aspeed_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 scalar_t__ max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int aspeed_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct aspeed_wdt_config *config;
	const struct of_device_id *ofdid;
	struct aspeed_wdt *wdt;
	struct device_node *np;
	const char *reset_type;
	u32 duration;
	u32 status;
	int ret;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	/*
	 * The ast2400 wdt can run at PCLK, or 1MHz. The ast2500 only
	 * runs at 1MHz. We chose to always run at 1MHz, as there's no
	 * good reason to have a faster watchdog counter.
	 */
	wdt->wdd.info = &aspeed_wdt_info;
	wdt->wdd.ops = &aspeed_wdt_ops;
	wdt->wdd.max_hw_heartbeat_ms = WDT_MAX_TIMEOUT_MS;
	wdt->wdd.parent = dev;

	wdt->wdd.timeout = WDT_DEFAULT_TIMEOUT;
	watchdog_init_timeout(&wdt->wdd, 0, dev);

	np = dev->of_node;

	ofdid = of_match_node(aspeed_wdt_of_table, np);
	if (!ofdid)
		return -EINVAL;
	config = ofdid->data;

	wdt->ctrl = WDT_CTRL_1MHZ_CLK;

	/*
	 * Control reset on a per-device basis to ensure the
	 * host is not affected by a BMC reboot
	 */
	ret = of_property_read_string(np, "aspeed,reset-type", &reset_type);
	if (ret) {
		wdt->ctrl |= WDT_CTRL_RESET_MODE_SOC | WDT_CTRL_RESET_SYSTEM;
	} else {
		if (!strcmp(reset_type, "cpu"))
			wdt->ctrl |= WDT_CTRL_RESET_MODE_ARM_CPU |
				     WDT_CTRL_RESET_SYSTEM;
		else if (!strcmp(reset_type, "soc"))
			wdt->ctrl |= WDT_CTRL_RESET_MODE_SOC |
				     WDT_CTRL_RESET_SYSTEM;
		else if (!strcmp(reset_type, "system"))
			wdt->ctrl |= WDT_CTRL_RESET_MODE_FULL_CHIP |
				     WDT_CTRL_RESET_SYSTEM;
		else if (strcmp(reset_type, "none"))
			return -EINVAL;
	}
	if (of_property_read_bool(np, "aspeed,external-signal"))
		wdt->ctrl |= WDT_CTRL_WDT_EXT;
	if (of_property_read_bool(np, "aspeed,alt-boot"))
		wdt->ctrl |= WDT_CTRL_BOOT_SECONDARY;

	if (readl(wdt->base + WDT_CTRL) & WDT_CTRL_ENABLE)  {
		/*
		 * The watchdog is running, but invoke aspeed_wdt_start() to
		 * write wdt->ctrl to WDT_CTRL to ensure the watchdog's
		 * configuration conforms to the driver's expectations.
		 * Primarily, ensure we're using the 1MHz clock source.
		 */
		aspeed_wdt_start(&wdt->wdd);
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	}

	if ((of_device_is_compatible(np, "aspeed,ast2500-wdt")) ||
		(of_device_is_compatible(np, "aspeed,ast2600-wdt"))) {
		u32 reg = readl(wdt->base + WDT_RESET_WIDTH);

		reg &= config->ext_pulse_width_mask;
		if (of_property_read_bool(np, "aspeed,ext-push-pull"))
			reg |= WDT_PUSH_PULL_MAGIC;
		else
			reg |= WDT_OPEN_DRAIN_MAGIC;

		writel(reg, wdt->base + WDT_RESET_WIDTH);

		reg &= config->ext_pulse_width_mask;
		if (of_property_read_bool(np, "aspeed,ext-active-high"))
			reg |= WDT_ACTIVE_HIGH_MAGIC;
		else
			reg |= WDT_ACTIVE_LOW_MAGIC;

		writel(reg, wdt->base + WDT_RESET_WIDTH);
	}

	if (!of_property_read_u32(np, "aspeed,ext-pulse-duration", &duration)) {
		u32 max_duration = config->ext_pulse_width_mask + 1;

		if (duration == 0 || duration > max_duration) {
			dev_err(dev, "Invalid pulse duration: %uus\n",
				duration);
			duration = max(1U, min(max_duration, duration));
			dev_info(dev, "Pulse duration set to %uus\n",
				 duration);
		}

		/*
		 * The watchdog is always configured with a 1MHz source, so
		 * there is no need to scale the microsecond value. However we
		 * need to offset it - from the datasheet:
		 *
		 * "This register decides the asserting duration of wdt_ext and
		 * wdt_rstarm signal. The default value is 0xFF. It means the
		 * default asserting duration of wdt_ext and wdt_rstarm is
		 * 256us."
		 *
		 * This implies a value of 0 gives a 1us pulse.
		 */
		writel(duration - 1, wdt->base + WDT_RESET_WIDTH);
	}

	status = readl(wdt->base + WDT_TIMEOUT_STATUS);
	if (status & WDT_TIMEOUT_STATUS_BOOT_SECONDARY) {
		wdt->wdd.bootstatus = WDIOF_CARDRESET;

		if (of_device_is_compatible(np, "aspeed,ast2400-wdt") ||
		    of_device_is_compatible(np, "aspeed,ast2500-wdt"))
			wdt->wdd.groups = bswitch_groups;
	}

	dev_set_drvdata(dev, wdt);

	return devm_watchdog_register_device(dev, &wdt->wdd);
}