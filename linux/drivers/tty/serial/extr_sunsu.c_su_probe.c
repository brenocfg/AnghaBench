#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t line; scalar_t__ type; int uartclk; int /*<<< orphan*/  membase; int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; TYPE_2__* dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  lock; } ;
struct uart_sunsu_port {int su_type; int /*<<< orphan*/  reg_size; TYPE_3__ port; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/ * irqs; } ;
struct platform_device {struct resource* resource; TYPE_2__ dev; TYPE_1__ archdata; } ;
struct device_node {int dummy; } ;
typedef  enum su_type { ____Placeholder_su_type } su_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PORT_UNKNOWN ; 
 int /*<<< orphan*/  SUNSU_CONSOLE () ; 
 int SU_BASE_BAUD ; 
 scalar_t__ SU_PORT_KBD ; 
 scalar_t__ SU_PORT_MS ; 
 int SU_PORT_PORT ; 
 size_t UART_NR ; 
 int /*<<< orphan*/  UPF_BOOT_AUTOCONF ; 
 int /*<<< orphan*/  kfree (struct uart_sunsu_port*) ; 
 struct uart_sunsu_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t nr_inst ; 
 int /*<<< orphan*/  of_ioremap (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_iounmap (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_node_name_eq (struct device_node*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int su_get_type (struct device_node*) ; 
 int /*<<< orphan*/  sunserial_console_match (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  sunsu_autoconfig (struct uart_sunsu_port*) ; 
 int sunsu_kbd_ms_init (struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  sunsu_pops ; 
 struct uart_sunsu_port* sunsu_ports ; 
 int /*<<< orphan*/  sunsu_reg ; 
 int uart_add_one_port (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int su_probe(struct platform_device *op)
{
	struct device_node *dp = op->dev.of_node;
	struct uart_sunsu_port *up;
	struct resource *rp;
	enum su_type type;
	bool ignore_line;
	int err;

	type = su_get_type(dp);
	if (type == SU_PORT_PORT) {
		if (nr_inst >= UART_NR)
			return -EINVAL;
		up = &sunsu_ports[nr_inst];
	} else {
		up = kzalloc(sizeof(*up), GFP_KERNEL);
		if (!up)
			return -ENOMEM;
	}

	up->port.line = nr_inst;

	spin_lock_init(&up->port.lock);

	up->su_type = type;

	rp = &op->resource[0];
	up->port.mapbase = rp->start;
	up->reg_size = resource_size(rp);
	up->port.membase = of_ioremap(rp, 0, up->reg_size, "su");
	if (!up->port.membase) {
		if (type != SU_PORT_PORT)
			kfree(up);
		return -ENOMEM;
	}

	up->port.irq = op->archdata.irqs[0];

	up->port.dev = &op->dev;

	up->port.type = PORT_UNKNOWN;
	up->port.uartclk = (SU_BASE_BAUD * 16);

	err = 0;
	if (up->su_type == SU_PORT_KBD || up->su_type == SU_PORT_MS) {
		err = sunsu_kbd_ms_init(up);
		if (err) {
			of_iounmap(&op->resource[0],
				   up->port.membase, up->reg_size);
			kfree(up);
			return err;
		}
		platform_set_drvdata(op, up);

		nr_inst++;

		return 0;
	}

	up->port.flags |= UPF_BOOT_AUTOCONF;

	sunsu_autoconfig(up);

	err = -ENODEV;
	if (up->port.type == PORT_UNKNOWN)
		goto out_unmap;

	up->port.ops = &sunsu_pops;

	ignore_line = false;
	if (of_node_name_eq(dp, "rsc-console") ||
	    of_node_name_eq(dp, "lom-console"))
		ignore_line = true;

	sunserial_console_match(SUNSU_CONSOLE(), dp,
				&sunsu_reg, up->port.line,
				ignore_line);
	err = uart_add_one_port(&sunsu_reg, &up->port);
	if (err)
		goto out_unmap;

	platform_set_drvdata(op, up);

	nr_inst++;

	return 0;

out_unmap:
	of_iounmap(&op->resource[0], up->port.membase, up->reg_size);
	kfree(up);
	return err;
}