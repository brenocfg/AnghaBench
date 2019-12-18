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
struct irq_chip {char* name; int /*<<< orphan*/  irq_bus_sync_unlock; int /*<<< orphan*/  irq_bus_lock; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; } ;
struct gpio_chip {char* label; int base; int can_sleep; scalar_t__ ngpio; int /*<<< orphan*/  set_config; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  owner; int /*<<< orphan*/ * parent; } ;
struct gbphy_device_id {int dummy; } ;
struct gbphy_device {int /*<<< orphan*/  dev; TYPE_1__* cport_desc; int /*<<< orphan*/  bundle; } ;
struct gb_gpio_controller {struct gb_gpio_controller* lines; scalar_t__ line_max; struct gpio_chip chip; int /*<<< orphan*/  irq_lock; struct irq_chip irqc; struct gbphy_device* gbphy_dev; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct gb_connection* gb_connection_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int gb_connection_enable_tx (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_gpio_controller*) ; 
 int /*<<< orphan*/  gb_gbphy_set_data (struct gbphy_device*,struct gb_gpio_controller*) ; 
 int gb_gpio_controller_setup (struct gb_gpio_controller*) ; 
 int /*<<< orphan*/  gb_gpio_direction_input ; 
 int /*<<< orphan*/  gb_gpio_direction_output ; 
 int /*<<< orphan*/  gb_gpio_free ; 
 int /*<<< orphan*/  gb_gpio_get ; 
 int /*<<< orphan*/  gb_gpio_get_direction ; 
 int /*<<< orphan*/  gb_gpio_irq_bus_lock ; 
 int /*<<< orphan*/  gb_gpio_irq_bus_sync_unlock ; 
 int /*<<< orphan*/  gb_gpio_irq_mask ; 
 int /*<<< orphan*/  gb_gpio_irq_set_type ; 
 int /*<<< orphan*/  gb_gpio_irq_unmask ; 
 int /*<<< orphan*/  gb_gpio_request ; 
 int /*<<< orphan*/  gb_gpio_request_handler ; 
 int /*<<< orphan*/  gb_gpio_set ; 
 int /*<<< orphan*/  gb_gpio_set_config ; 
 int /*<<< orphan*/  gbphy_runtime_put_autosuspend (struct gbphy_device*) ; 
 int gpiochip_add (struct gpio_chip*) ; 
 int gpiochip_irqchip_add (struct gpio_chip*,struct irq_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (struct gpio_chip*) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  kfree (struct gb_gpio_controller*) ; 
 struct gb_gpio_controller* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_gpio_probe(struct gbphy_device *gbphy_dev,
			 const struct gbphy_device_id *id)
{
	struct gb_connection *connection;
	struct gb_gpio_controller *ggc;
	struct gpio_chip *gpio;
	struct irq_chip *irqc;
	int ret;

	ggc = kzalloc(sizeof(*ggc), GFP_KERNEL);
	if (!ggc)
		return -ENOMEM;

	connection =
		gb_connection_create(gbphy_dev->bundle,
				     le16_to_cpu(gbphy_dev->cport_desc->id),
				     gb_gpio_request_handler);
	if (IS_ERR(connection)) {
		ret = PTR_ERR(connection);
		goto exit_ggc_free;
	}

	ggc->connection = connection;
	gb_connection_set_data(connection, ggc);
	ggc->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, ggc);

	ret = gb_connection_enable_tx(connection);
	if (ret)
		goto exit_connection_destroy;

	ret = gb_gpio_controller_setup(ggc);
	if (ret)
		goto exit_connection_disable;

	irqc = &ggc->irqc;
	irqc->irq_mask = gb_gpio_irq_mask;
	irqc->irq_unmask = gb_gpio_irq_unmask;
	irqc->irq_set_type = gb_gpio_irq_set_type;
	irqc->irq_bus_lock = gb_gpio_irq_bus_lock;
	irqc->irq_bus_sync_unlock = gb_gpio_irq_bus_sync_unlock;
	irqc->name = "greybus_gpio";

	mutex_init(&ggc->irq_lock);

	gpio = &ggc->chip;

	gpio->label = "greybus_gpio";
	gpio->parent = &gbphy_dev->dev;
	gpio->owner = THIS_MODULE;

	gpio->request = gb_gpio_request;
	gpio->free = gb_gpio_free;
	gpio->get_direction = gb_gpio_get_direction;
	gpio->direction_input = gb_gpio_direction_input;
	gpio->direction_output = gb_gpio_direction_output;
	gpio->get = gb_gpio_get;
	gpio->set = gb_gpio_set;
	gpio->set_config = gb_gpio_set_config;
	gpio->base = -1;		/* Allocate base dynamically */
	gpio->ngpio = ggc->line_max + 1;
	gpio->can_sleep = true;

	ret = gb_connection_enable(connection);
	if (ret)
		goto exit_line_free;

	ret = gpiochip_add(gpio);
	if (ret) {
		dev_err(&gbphy_dev->dev, "failed to add gpio chip: %d\n", ret);
		goto exit_line_free;
	}

	ret = gpiochip_irqchip_add(gpio, irqc, 0, handle_level_irq,
				   IRQ_TYPE_NONE);
	if (ret) {
		dev_err(&gbphy_dev->dev, "failed to add irq chip: %d\n", ret);
		goto exit_gpiochip_remove;
	}

	gbphy_runtime_put_autosuspend(gbphy_dev);
	return 0;

exit_gpiochip_remove:
	gpiochip_remove(gpio);
exit_line_free:
	kfree(ggc->lines);
exit_connection_disable:
	gb_connection_disable(connection);
exit_connection_destroy:
	gb_connection_destroy(connection);
exit_ggc_free:
	kfree(ggc);
	return ret;
}