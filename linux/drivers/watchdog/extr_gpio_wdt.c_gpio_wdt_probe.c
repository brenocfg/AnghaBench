#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {unsigned int max_hw_heartbeat_ms; int /*<<< orphan*/  timeout; struct device* parent; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct gpio_wdt_priv {TYPE_1__ wdd; scalar_t__ always_running; int /*<<< orphan*/  gpiod; int /*<<< orphan*/  hw_algo; } ;
struct device_node {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_IN ; 
 int GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  HW_ALGO_LEVEL ; 
 int /*<<< orphan*/  HW_ALGO_TOGGLE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_TIMEOUT_DEF ; 
 int /*<<< orphan*/  SOFT_TIMEOUT_MIN ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,int /*<<< orphan*/ *,int) ; 
 struct gpio_wdt_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_wdt_ident ; 
 int /*<<< orphan*/  gpio_wdt_ops ; 
 int /*<<< orphan*/  gpio_wdt_start (TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_wdt_priv*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct gpio_wdt_priv*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 

__attribute__((used)) static int gpio_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct gpio_wdt_priv *priv;
	enum gpiod_flags gflags;
	unsigned int hw_margin;
	const char *algo;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	ret = of_property_read_string(np, "hw_algo", &algo);
	if (ret)
		return ret;
	if (!strcmp(algo, "toggle")) {
		priv->hw_algo = HW_ALGO_TOGGLE;
		gflags = GPIOD_IN;
	} else if (!strcmp(algo, "level")) {
		priv->hw_algo = HW_ALGO_LEVEL;
		gflags = GPIOD_OUT_LOW;
	} else {
		return -EINVAL;
	}

	priv->gpiod = devm_gpiod_get(dev, NULL, gflags);
	if (IS_ERR(priv->gpiod))
		return PTR_ERR(priv->gpiod);

	ret = of_property_read_u32(np,
				   "hw_margin_ms", &hw_margin);
	if (ret)
		return ret;
	/* Disallow values lower than 2 and higher than 65535 ms */
	if (hw_margin < 2 || hw_margin > 65535)
		return -EINVAL;

	priv->always_running = of_property_read_bool(np,
						     "always-running");

	watchdog_set_drvdata(&priv->wdd, priv);

	priv->wdd.info		= &gpio_wdt_ident;
	priv->wdd.ops		= &gpio_wdt_ops;
	priv->wdd.min_timeout	= SOFT_TIMEOUT_MIN;
	priv->wdd.max_hw_heartbeat_ms = hw_margin;
	priv->wdd.parent	= dev;
	priv->wdd.timeout	= SOFT_TIMEOUT_DEF;

	watchdog_init_timeout(&priv->wdd, 0, dev);
	watchdog_set_nowayout(&priv->wdd, nowayout);

	watchdog_stop_on_reboot(&priv->wdd);

	if (priv->always_running)
		gpio_wdt_start(&priv->wdd);

	return devm_watchdog_register_device(dev, &priv->wdd);
}