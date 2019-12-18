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
struct TYPE_2__ {int /*<<< orphan*/  serial_out; scalar_t__ mapbase; int /*<<< orphan*/  flags; int /*<<< orphan*/  iotype; struct f815xxa_data* private_data; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct serial_private {struct pci_dev* dev; } ;
struct pciserial_board {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct f815xxa_data {int idx; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UPF_IOREMAP ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 struct f815xxa_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f815xxa_mem_serial_out ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pci_fintek_f815xxa_setup(struct serial_private *priv,
			    const struct pciserial_board *board,
			    struct uart_8250_port *port, int idx)
{
	struct pci_dev *pdev = priv->dev;
	struct f815xxa_data *data;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->idx = idx;
	spin_lock_init(&data->lock);

	port->port.private_data = data;
	port->port.iotype = UPIO_MEM;
	port->port.flags |= UPF_IOREMAP;
	port->port.mapbase = pci_resource_start(pdev, 0) + 8 * idx;
	port->port.serial_out = f815xxa_mem_serial_out;

	return 0;
}