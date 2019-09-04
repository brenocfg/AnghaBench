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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_EVENTS_ENABLE ; 
 int /*<<< orphan*/  GPIO_INPUT_INVERT ; 
 int /*<<< orphan*/  GPIO_NEGATIVE_EDGE_EN ; 
 int /*<<< orphan*/  GPIO_NEGATIVE_EDGE_STS ; 
 int /*<<< orphan*/  GPIO_POSITIVE_EDGE_EN ; 
 int /*<<< orphan*/  GPIO_POSITIVE_EDGE_STS ; 
 int /*<<< orphan*/  OLPC_GPIO_LID ; 
 int /*<<< orphan*/  cs5535_gpio_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_set_irq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_setup_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lid_inverted ; 
 int /*<<< orphan*/  sci_irq ; 

__attribute__((used)) static int setup_lid_events(void)
{
	int r;

	r = gpio_request(OLPC_GPIO_LID, "OLPC-LID");
	if (r)
		return r;

	gpio_direction_input(OLPC_GPIO_LID);

	cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_INPUT_INVERT);
	lid_inverted = 0;

	/* Clear edge detection and event enable for now */
	cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);
	cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_NEGATIVE_EDGE_EN);
	cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_POSITIVE_EDGE_EN);
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_POSITIVE_EDGE_STS);

	/* Set the LID to cause an PME event on group 6 */
	cs5535_gpio_setup_event(OLPC_GPIO_LID, 6, 1);

	/* Set PME group 6 to fire the SCI interrupt */
	cs5535_gpio_set_irq(6, sci_irq);

	/* Enable the event */
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);

	return 0;
}