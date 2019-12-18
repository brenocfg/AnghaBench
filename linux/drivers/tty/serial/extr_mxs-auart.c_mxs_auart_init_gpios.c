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
struct mxs_auart_port {int /*<<< orphan*/ * gpio_irq; int /*<<< orphan*/  gpios; int /*<<< orphan*/  flags; } ;
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;

/* Variables and functions */
 int /*<<< orphan*/  CTS_AT_AUART () ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MXS_AUART_RTSCTS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTS_AT_AUART () ; 
 int UART_GPIO_MAX ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int gpiod_get_direction (struct gpio_desc*) ; 
 int /*<<< orphan*/  gpiod_to_irq (struct gpio_desc*) ; 
 int /*<<< orphan*/  mctrl_gpio_init_noauto (struct device*,int /*<<< orphan*/ ) ; 
 struct gpio_desc* mctrl_gpio_to_gpiod (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxs_auart_init_gpios(struct mxs_auart_port *s, struct device *dev)
{
	enum mctrl_gpio_idx i;
	struct gpio_desc *gpiod;

	s->gpios = mctrl_gpio_init_noauto(dev, 0);
	if (IS_ERR(s->gpios))
		return PTR_ERR(s->gpios);

	/* Block (enabled before) DMA option if RTS or CTS is GPIO line */
	if (!RTS_AT_AUART() || !CTS_AT_AUART()) {
		if (test_bit(MXS_AUART_RTSCTS, &s->flags))
			dev_warn(dev,
				 "DMA and flow control via gpio may cause some problems. DMA disabled!\n");
		clear_bit(MXS_AUART_RTSCTS, &s->flags);
	}

	for (i = 0; i < UART_GPIO_MAX; i++) {
		gpiod = mctrl_gpio_to_gpiod(s->gpios, i);
		if (gpiod && (gpiod_get_direction(gpiod) == 1))
			s->gpio_irq[i] = gpiod_to_irq(gpiod);
		else
			s->gpio_irq[i] = -EINVAL;
	}

	return 0;
}