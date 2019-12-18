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
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct serio {int /*<<< orphan*/  base; struct serio* io; int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; TYPE_2__ dev; struct serio* port_data; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  write; TYPE_1__ id; } ;
struct amba_kmi_port {int /*<<< orphan*/  base; struct amba_kmi_port* io; int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; TYPE_2__ dev; struct amba_kmi_port* port_data; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  write; TYPE_1__ id; } ;
struct amba_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
struct amba_device {int /*<<< orphan*/ * irq; int /*<<< orphan*/  dev; TYPE_3__ res; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERIO_8042 ; 
 int /*<<< orphan*/  amba_kmi_close ; 
 int /*<<< orphan*/  amba_kmi_open ; 
 int /*<<< orphan*/  amba_kmi_write ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int amba_request_regions (struct amba_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct serio*) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct serio*) ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_3__*) ; 
 int /*<<< orphan*/  serio_register_port (struct serio*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amba_kmi_probe(struct amba_device *dev,
	const struct amba_id *id)
{
	struct amba_kmi_port *kmi;
	struct serio *io;
	int ret;

	ret = amba_request_regions(dev, NULL);
	if (ret)
		return ret;

	kmi = kzalloc(sizeof(struct amba_kmi_port), GFP_KERNEL);
	io = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!kmi || !io) {
		ret = -ENOMEM;
		goto out;
	}


	io->id.type	= SERIO_8042;
	io->write	= amba_kmi_write;
	io->open	= amba_kmi_open;
	io->close	= amba_kmi_close;
	strlcpy(io->name, dev_name(&dev->dev), sizeof(io->name));
	strlcpy(io->phys, dev_name(&dev->dev), sizeof(io->phys));
	io->port_data	= kmi;
	io->dev.parent	= &dev->dev;

	kmi->io		= io;
	kmi->base	= ioremap(dev->res.start, resource_size(&dev->res));
	if (!kmi->base) {
		ret = -ENOMEM;
		goto out;
	}

	kmi->clk = clk_get(&dev->dev, "KMIREFCLK");
	if (IS_ERR(kmi->clk)) {
		ret = PTR_ERR(kmi->clk);
		goto unmap;
	}

	kmi->irq = dev->irq[0];
	amba_set_drvdata(dev, kmi);

	serio_register_port(kmi->io);
	return 0;

 unmap:
	iounmap(kmi->base);
 out:
	kfree(kmi);
	kfree(io);
	amba_release_regions(dev);
	return ret;
}