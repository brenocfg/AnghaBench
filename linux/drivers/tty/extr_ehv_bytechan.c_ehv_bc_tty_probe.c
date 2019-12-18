#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ops; } ;
struct ehv_bc_data {unsigned int handle; scalar_t__ rx_irq; scalar_t__ tx_irq; TYPE_1__ port; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; scalar_t__ tail; scalar_t__ head; } ;
struct device_node {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ NO_IRQ ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct ehv_bc_data* bcs ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct ehv_bc_data*) ; 
 TYPE_2__* ehv_bc_driver ; 
 int /*<<< orphan*/  ehv_bc_tty_port_ops ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 void* irq_of_parse_and_map (struct device_node*,int) ; 
 int /*<<< orphan*/  memset (struct ehv_bc_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 unsigned int stdout_bc ; 
 int /*<<< orphan*/  tty_port_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_register_device (TYPE_1__*,TYPE_2__*,unsigned int,TYPE_3__*) ; 

__attribute__((used)) static int ehv_bc_tty_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct ehv_bc_data *bc;
	const uint32_t *iprop;
	unsigned int handle;
	int ret;
	static unsigned int index = 1;
	unsigned int i;

	iprop = of_get_property(np, "hv-handle", NULL);
	if (!iprop) {
		dev_err(&pdev->dev, "no 'hv-handle' property in %pOFn node\n",
			np);
		return -ENODEV;
	}

	/* We already told the console layer that the index for the console
	 * device is zero, so we need to make sure that we use that index when
	 * we probe the console byte channel node.
	 */
	handle = be32_to_cpu(*iprop);
	i = (handle == stdout_bc) ? 0 : index++;
	bc = &bcs[i];

	bc->handle = handle;
	bc->head = 0;
	bc->tail = 0;
	spin_lock_init(&bc->lock);

	bc->rx_irq = irq_of_parse_and_map(np, 0);
	bc->tx_irq = irq_of_parse_and_map(np, 1);
	if ((bc->rx_irq == NO_IRQ) || (bc->tx_irq == NO_IRQ)) {
		dev_err(&pdev->dev, "no 'interrupts' property in %pOFn node\n",
			np);
		ret = -ENODEV;
		goto error;
	}

	tty_port_init(&bc->port);
	bc->port.ops = &ehv_bc_tty_port_ops;

	bc->dev = tty_port_register_device(&bc->port, ehv_bc_driver, i,
			&pdev->dev);
	if (IS_ERR(bc->dev)) {
		ret = PTR_ERR(bc->dev);
		dev_err(&pdev->dev, "could not register tty (ret=%i)\n", ret);
		goto error;
	}

	dev_set_drvdata(&pdev->dev, bc);

	dev_info(&pdev->dev, "registered /dev/%s%u for byte channel %u\n",
		ehv_bc_driver->name, i, bc->handle);

	return 0;

error:
	tty_port_destroy(&bc->port);
	irq_dispose_mapping(bc->tx_irq);
	irq_dispose_mapping(bc->rx_irq);

	memset(bc, 0, sizeof(struct ehv_bc_data));
	return ret;
}