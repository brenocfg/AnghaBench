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
struct dcon_priv {scalar_t__ curr_src; scalar_t__ pending_src; TYPE_1__* client; } ;
struct dcon_gpio {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dcon_gpio*) ; 
 int DCON_IRQ ; 
 scalar_t__ DCON_SOURCE_CPU ; 
 scalar_t__ DCON_SOURCE_DCON ; 
 int EIO ; 
 int /*<<< orphan*/  GPIO_EVENTS_ENABLE ; 
 int /*<<< orphan*/  GPIO_FE7_SEL ; 
 int /*<<< orphan*/  GPIO_FLTR7_AMOUNT ; 
 int /*<<< orphan*/  GPIO_INPUT_EVENT_COUNT ; 
 int /*<<< orphan*/  GPIO_INPUT_FILTER ; 
 int /*<<< orphan*/  GPIO_INPUT_INVERT ; 
 int /*<<< orphan*/  GPIO_NEGATIVE_EDGE_EN ; 
 int /*<<< orphan*/  GPIO_NEGATIVE_EDGE_STS ; 
 int /*<<< orphan*/  GPIO_OUTPUT_VAL ; 
 int /*<<< orphan*/  GPIO_POSITIVE_EDGE_STS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 size_t OLPC_DCON_BLANK ; 
 size_t OLPC_DCON_IRQ ; 
 size_t OLPC_DCON_LOAD ; 
 size_t OLPC_DCON_STAT0 ; 
 size_t OLPC_DCON_STAT1 ; 
 int /*<<< orphan*/  OLPC_GPIO_DCON_BLANK ; 
 int /*<<< orphan*/  OLPC_GPIO_DCON_IRQ ; 
 int /*<<< orphan*/  OLPC_GPIO_DCON_LOAD ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cs5535_gpio_isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_set_irq (int,int) ; 
 int /*<<< orphan*/  cs5535_gpio_setup_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcon_interrupt ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gpios ; 
 struct dcon_gpio* gpios_asis ; 
 unsigned char inb (int) ; 
 int /*<<< orphan*/  outb (unsigned char,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct dcon_priv*) ; 

__attribute__((used)) static int dcon_init_xo_1(struct dcon_priv *dcon)
{
	unsigned char lob;
	int ret, i;
	const struct dcon_gpio *pin = &gpios_asis[0];

	for (i = 0; i < ARRAY_SIZE(gpios_asis); i++) {
		gpios[i] = devm_gpiod_get(&dcon->client->dev, pin[i].name,
					  pin[i].flags);
		if (IS_ERR(gpios[i])) {
			ret = PTR_ERR(gpios[i]);
			pr_err("failed to request %s GPIO: %d\n", pin[i].name,
			       ret);
			return ret;
		}
	}

	/* Turn off the event enable for GPIO7 just to be safe */
	cs5535_gpio_clear(OLPC_GPIO_DCON_IRQ, GPIO_EVENTS_ENABLE);

	/*
	 * Determine the current state by reading the GPIO bit; earlier
	 * stages of the boot process have established the state.
	 *
	 * Note that we read GPIO_OUTPUT_VAL rather than GPIO_READ_BACK here;
	 * this is because OFW will disable input for the pin and set a value..
	 * READ_BACK will only contain a valid value if input is enabled and
	 * then a value is set.  So, future readings of the pin can use
	 * READ_BACK, but the first one cannot.  Awesome, huh?
	 */
	dcon->curr_src = cs5535_gpio_isset(OLPC_GPIO_DCON_LOAD, GPIO_OUTPUT_VAL)
		? DCON_SOURCE_CPU
		: DCON_SOURCE_DCON;
	dcon->pending_src = dcon->curr_src;

	/* Set the directions for the GPIO pins */
	gpiod_direction_input(gpios[OLPC_DCON_STAT0]);
	gpiod_direction_input(gpios[OLPC_DCON_STAT1]);
	gpiod_direction_input(gpios[OLPC_DCON_IRQ]);
	gpiod_direction_input(gpios[OLPC_DCON_BLANK]);
	gpiod_direction_output(gpios[OLPC_DCON_LOAD],
			       dcon->curr_src == DCON_SOURCE_CPU);

	/* Set up the interrupt mappings */

	/* Set the IRQ to pair 2 */
	cs5535_gpio_setup_event(OLPC_GPIO_DCON_IRQ, 2, 0);

	/* Enable group 2 to trigger the DCON interrupt */
	cs5535_gpio_set_irq(2, DCON_IRQ);

	/* Select edge level for interrupt (in PIC) */
	lob = inb(0x4d0);
	lob &= ~(1 << DCON_IRQ);
	outb(lob, 0x4d0);

	/* Register the interrupt handler */
	if (request_irq(DCON_IRQ, &dcon_interrupt, 0, "DCON", dcon)) {
		pr_err("failed to request DCON's irq\n");
		return -EIO;
	}

	/* Clear INV_EN for GPIO7 (DCONIRQ) */
	cs5535_gpio_clear(OLPC_GPIO_DCON_IRQ, GPIO_INPUT_INVERT);

	/* Enable filter for GPIO12 (DCONBLANK) */
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_INPUT_FILTER);

	/* Disable filter for GPIO7 */
	cs5535_gpio_clear(OLPC_GPIO_DCON_IRQ, GPIO_INPUT_FILTER);

	/* Disable event counter for GPIO7 (DCONIRQ) and GPIO12 (DCONBLANK) */
	cs5535_gpio_clear(OLPC_GPIO_DCON_IRQ, GPIO_INPUT_EVENT_COUNT);
	cs5535_gpio_clear(OLPC_GPIO_DCON_BLANK, GPIO_INPUT_EVENT_COUNT);

	/* Add GPIO12 to the Filter Event Pair #7 */
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_FE7_SEL);

	/* Turn off negative Edge Enable for GPIO12 */
	cs5535_gpio_clear(OLPC_GPIO_DCON_BLANK, GPIO_NEGATIVE_EDGE_EN);

	/* Enable negative Edge Enable for GPIO7 */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_NEGATIVE_EDGE_EN);

	/* Zero the filter amount for Filter Event Pair #7 */
	cs5535_gpio_set(0, GPIO_FLTR7_AMOUNT);

	/* Clear the negative edge status for GPIO7 and GPIO12 */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_NEGATIVE_EDGE_STS);

	/* FIXME:  Clear the positive status as well, just to be sure */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_POSITIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_POSITIVE_EDGE_STS);

	/* Enable events for GPIO7 (DCONIRQ) and GPIO12 (DCONBLANK) */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_EVENTS_ENABLE);
	cs5535_gpio_set(OLPC_GPIO_DCON_BLANK, GPIO_EVENTS_ENABLE);

	return 0;
}