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
struct TYPE_2__ {char* label; int base; int /*<<< orphan*/  set_multiple; int /*<<< orphan*/  set; int /*<<< orphan*/  get_multiple; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  names; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  owner; struct device* parent; } ;
struct gpiomm_gpio {TYPE_1__ chip; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIOMM_EXTENT ; 
 int /*<<< orphan*/  GPIOMM_NGPIO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__* base ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 char* dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct gpiomm_gpio*) ; 
 struct gpiomm_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,scalar_t__,scalar_t__,char const* const) ; 
 int /*<<< orphan*/  gpiomm_gpio_direction_input ; 
 int /*<<< orphan*/  gpiomm_gpio_direction_output ; 
 int /*<<< orphan*/  gpiomm_gpio_get ; 
 int /*<<< orphan*/  gpiomm_gpio_get_direction ; 
 int /*<<< orphan*/  gpiomm_gpio_get_multiple ; 
 int /*<<< orphan*/  gpiomm_gpio_set ; 
 int /*<<< orphan*/  gpiomm_gpio_set_multiple ; 
 int /*<<< orphan*/  gpiomm_names ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpiomm_probe(struct device *dev, unsigned int id)
{
	struct gpiomm_gpio *gpiommgpio;
	const char *const name = dev_name(dev);
	int err;

	gpiommgpio = devm_kzalloc(dev, sizeof(*gpiommgpio), GFP_KERNEL);
	if (!gpiommgpio)
		return -ENOMEM;

	if (!devm_request_region(dev, base[id], GPIOMM_EXTENT, name)) {
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + GPIOMM_EXTENT);
		return -EBUSY;
	}

	gpiommgpio->chip.label = name;
	gpiommgpio->chip.parent = dev;
	gpiommgpio->chip.owner = THIS_MODULE;
	gpiommgpio->chip.base = -1;
	gpiommgpio->chip.ngpio = GPIOMM_NGPIO;
	gpiommgpio->chip.names = gpiomm_names;
	gpiommgpio->chip.get_direction = gpiomm_gpio_get_direction;
	gpiommgpio->chip.direction_input = gpiomm_gpio_direction_input;
	gpiommgpio->chip.direction_output = gpiomm_gpio_direction_output;
	gpiommgpio->chip.get = gpiomm_gpio_get;
	gpiommgpio->chip.get_multiple = gpiomm_gpio_get_multiple;
	gpiommgpio->chip.set = gpiomm_gpio_set;
	gpiommgpio->chip.set_multiple = gpiomm_gpio_set_multiple;
	gpiommgpio->base = base[id];

	spin_lock_init(&gpiommgpio->lock);

	err = devm_gpiochip_add_data(dev, &gpiommgpio->chip, gpiommgpio);
	if (err) {
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		return err;
	}

	/* initialize all GPIO as output */
	outb(0x80, base[id] + 3);
	outb(0x00, base[id]);
	outb(0x00, base[id] + 1);
	outb(0x00, base[id] + 2);
	outb(0x80, base[id] + 7);
	outb(0x00, base[id] + 4);
	outb(0x00, base[id] + 5);
	outb(0x00, base[id] + 6);

	return 0;
}