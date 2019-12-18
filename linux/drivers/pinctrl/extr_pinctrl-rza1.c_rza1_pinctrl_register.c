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
struct rza1_port {unsigned int id; int /*<<< orphan*/  lock; struct pinctrl_pin_desc* pins; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {unsigned int npins; struct pinctrl_pin_desc* pins; } ;
struct rza1_pinctrl {int /*<<< orphan*/  dev; int /*<<< orphan*/  pctl; TYPE_1__ desc; int /*<<< orphan*/  base; struct rza1_port* ports; struct pinctrl_pin_desc* pins; } ;
struct pinctrl_pin_desc {unsigned int number; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int RZA1_NPINS ; 
 unsigned int RZA1_NPORTS ; 
 unsigned int RZA1_PINS_PER_PORT ; 
 unsigned int RZA1_PIN_ID_TO_PIN (unsigned int) ; 
 unsigned int RZA1_PIN_ID_TO_PORT (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int devm_pinctrl_register_and_init (int /*<<< orphan*/ ,TYPE_1__*,struct rza1_pinctrl*,int /*<<< orphan*/ *) ; 
 int pinctrl_enable (int /*<<< orphan*/ ) ; 
 int rza1_gpio_register (struct rza1_pinctrl*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rza1_pinctrl_register(struct rza1_pinctrl *rza1_pctl)
{
	struct pinctrl_pin_desc *pins;
	struct rza1_port *ports;
	unsigned int i;
	int ret;

	pins = devm_kcalloc(rza1_pctl->dev, RZA1_NPINS, sizeof(*pins),
			    GFP_KERNEL);
	ports = devm_kcalloc(rza1_pctl->dev, RZA1_NPORTS, sizeof(*ports),
			     GFP_KERNEL);
	if (!pins || !ports)
		return -ENOMEM;

	rza1_pctl->pins		= pins;
	rza1_pctl->desc.pins	= pins;
	rza1_pctl->desc.npins	= RZA1_NPINS;
	rza1_pctl->ports	= ports;

	for (i = 0; i < RZA1_NPINS; ++i) {
		unsigned int pin = RZA1_PIN_ID_TO_PIN(i);
		unsigned int port = RZA1_PIN_ID_TO_PORT(i);

		pins[i].number = i;
		pins[i].name = devm_kasprintf(rza1_pctl->dev, GFP_KERNEL,
					      "P%u-%u", port, pin);
		if (!pins[i].name)
			return -ENOMEM;

		if (i % RZA1_PINS_PER_PORT == 0) {
			/*
			 * Setup ports;
			 * they provide per-port lock and logical base address.
			 */
			unsigned int port_id = RZA1_PIN_ID_TO_PORT(i);

			ports[port_id].id	= port_id;
			ports[port_id].base	= rza1_pctl->base;
			ports[port_id].pins	= &pins[i];
			spin_lock_init(&ports[port_id].lock);
		}
	}

	ret = devm_pinctrl_register_and_init(rza1_pctl->dev, &rza1_pctl->desc,
					     rza1_pctl, &rza1_pctl->pctl);
	if (ret) {
		dev_err(rza1_pctl->dev,
			"RZ/A1 pin controller registration failed\n");
		return ret;
	}

	ret = pinctrl_enable(rza1_pctl->pctl);
	if (ret) {
		dev_err(rza1_pctl->dev,
			"RZ/A1 pin controller failed to start\n");
		return ret;
	}

	ret = rza1_gpio_register(rza1_pctl);
	if (ret) {
		dev_err(rza1_pctl->dev, "RZ/A1 GPIO registration failed\n");
		return ret;
	}

	return 0;
}