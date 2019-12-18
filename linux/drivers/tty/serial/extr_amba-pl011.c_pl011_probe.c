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
struct vendor_data {scalar_t__ access_32b; int /*<<< orphan*/  (* get_fifosize ) (struct amba_device*) ;int /*<<< orphan*/  reg_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  irq; int /*<<< orphan*/  iotype; } ;
struct uart_amba_port {int /*<<< orphan*/  type; TYPE_1__ port; int /*<<< orphan*/  fifosize; struct vendor_data* vendor; int /*<<< orphan*/  reg_offset; int /*<<< orphan*/  clk; } ;
struct amba_id {struct vendor_data* data; } ;
struct amba_device {int /*<<< orphan*/  res; int /*<<< orphan*/  dev; int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  amba_pl011_pops ; 
 int amba_rev (struct amba_device*) ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct uart_amba_port*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct uart_amba_port* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pl011_find_free_port () ; 
 int pl011_register_port (struct uart_amba_port*) ; 
 int pl011_setup_port (int /*<<< orphan*/ *,struct uart_amba_port*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct amba_device*) ; 

__attribute__((used)) static int pl011_probe(struct amba_device *dev, const struct amba_id *id)
{
	struct uart_amba_port *uap;
	struct vendor_data *vendor = id->data;
	int portnr, ret;

	portnr = pl011_find_free_port();
	if (portnr < 0)
		return portnr;

	uap = devm_kzalloc(&dev->dev, sizeof(struct uart_amba_port),
			   GFP_KERNEL);
	if (!uap)
		return -ENOMEM;

	uap->clk = devm_clk_get(&dev->dev, NULL);
	if (IS_ERR(uap->clk))
		return PTR_ERR(uap->clk);

	uap->reg_offset = vendor->reg_offset;
	uap->vendor = vendor;
	uap->fifosize = vendor->get_fifosize(dev);
	uap->port.iotype = vendor->access_32b ? UPIO_MEM32 : UPIO_MEM;
	uap->port.irq = dev->irq[0];
	uap->port.ops = &amba_pl011_pops;

	snprintf(uap->type, sizeof(uap->type), "PL011 rev%u", amba_rev(dev));

	ret = pl011_setup_port(&dev->dev, uap, &dev->res, portnr);
	if (ret)
		return ret;

	amba_set_drvdata(dev, uap);

	return pl011_register_port(uap);
}