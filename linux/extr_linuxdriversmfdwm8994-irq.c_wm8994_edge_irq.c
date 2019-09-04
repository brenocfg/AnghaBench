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
struct TYPE_2__ {int /*<<< orphan*/  irq_gpio; } ;
struct wm8994 {int /*<<< orphan*/  edge_irq; TYPE_1__ pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ gpio_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_nested_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wm8994_edge_irq(int irq, void *data)
{
	struct wm8994 *wm8994 = data;

	while (gpio_get_value_cansleep(wm8994->pdata.irq_gpio))
		handle_nested_irq(irq_create_mapping(wm8994->edge_irq, 0));

	return IRQ_HANDLED;
}