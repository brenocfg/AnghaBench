#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct serio {int /*<<< orphan*/  phys; int /*<<< orphan*/  name; TYPE_2__ dev; struct olpc_apsp* port_data; void* close; void* open; void* write; TYPE_1__ id; } ;
struct resource {int dummy; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct olpc_apsp {scalar_t__ irq; TYPE_3__* dev; struct serio* padio; struct serio* kbio; scalar_t__ base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned long CMD_STS_MASK ; 
 scalar_t__ COMMAND_FIFO_STATUS ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SERIO_8042 ; 
 int /*<<< orphan*/  SERIO_8042_XL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 scalar_t__ devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct olpc_apsp* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* olpc_apsp_close ; 
 void* olpc_apsp_open ; 
 int /*<<< orphan*/  olpc_apsp_rx ; 
 void* olpc_apsp_write ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct olpc_apsp*) ; 
 unsigned long readl (scalar_t__) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct olpc_apsp*) ; 
 int /*<<< orphan*/  serio_register_port (struct serio*) ; 
 int /*<<< orphan*/  serio_unregister_port (struct serio*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int olpc_apsp_probe(struct platform_device *pdev)
{
	struct serio *kb_serio, *pad_serio;
	struct olpc_apsp *priv;
	struct resource *res;
	struct device_node *np;
	unsigned long l;
	int error;

	priv = devm_kzalloc(&pdev->dev, sizeof(struct olpc_apsp), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	np = pdev->dev.of_node;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base)) {
		dev_err(&pdev->dev, "Failed to map WTM registers\n");
		return PTR_ERR(priv->base);
	}

	priv->irq = platform_get_irq(pdev, 0);
	if (priv->irq < 0)
		return priv->irq;

	l = readl(priv->base + COMMAND_FIFO_STATUS);
	if (!(l & CMD_STS_MASK)) {
		dev_err(&pdev->dev, "SP cannot accept commands.\n");
		return -EIO;
	}

	/* KEYBOARD */
	kb_serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!kb_serio)
		return -ENOMEM;
	kb_serio->id.type	= SERIO_8042_XL;
	kb_serio->write		= olpc_apsp_write;
	kb_serio->open		= olpc_apsp_open;
	kb_serio->close		= olpc_apsp_close;
	kb_serio->port_data	= priv;
	kb_serio->dev.parent	= &pdev->dev;
	strlcpy(kb_serio->name, "sp keyboard", sizeof(kb_serio->name));
	strlcpy(kb_serio->phys, "sp/serio0", sizeof(kb_serio->phys));
	priv->kbio		= kb_serio;
	serio_register_port(kb_serio);

	/* TOUCHPAD */
	pad_serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!pad_serio) {
		error = -ENOMEM;
		goto err_pad;
	}
	pad_serio->id.type	= SERIO_8042;
	pad_serio->write	= olpc_apsp_write;
	pad_serio->open		= olpc_apsp_open;
	pad_serio->close	= olpc_apsp_close;
	pad_serio->port_data	= priv;
	pad_serio->dev.parent	= &pdev->dev;
	strlcpy(pad_serio->name, "sp touchpad", sizeof(pad_serio->name));
	strlcpy(pad_serio->phys, "sp/serio1", sizeof(pad_serio->phys));
	priv->padio		= pad_serio;
	serio_register_port(pad_serio);

	error = request_irq(priv->irq, olpc_apsp_rx, 0, "olpc-apsp", priv);
	if (error) {
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		goto err_irq;
	}

	priv->dev = &pdev->dev;
	device_init_wakeup(priv->dev, 1);
	platform_set_drvdata(pdev, priv);

	dev_dbg(&pdev->dev, "probed successfully.\n");
	return 0;

err_irq:
	serio_unregister_port(pad_serio);
err_pad:
	serio_unregister_port(kb_serio);
	return error;
}