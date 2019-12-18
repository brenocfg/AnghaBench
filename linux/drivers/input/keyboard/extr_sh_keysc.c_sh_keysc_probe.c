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
struct sh_keysc_info {size_t mode; int scan_timing; int /*<<< orphan*/ * keycodes; } ;
struct sh_keysc_priv {int /*<<< orphan*/ * iomem_base; struct input_dev* input; struct sh_keysc_info pdata; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {char* phys; int keycodesize; int /*<<< orphan*/  keybit; int /*<<< orphan*/  keycodemax; int /*<<< orphan*/ * keycode; TYPE_2__ id; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * evbit; } ;
struct TYPE_6__ {int kymd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  KYCR1 ; 
 int SH_KEYSC_MAXKEYS ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_irq (int,struct platform_device*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sh_keysc_priv*) ; 
 struct sh_keysc_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sh_keysc_info*,int /*<<< orphan*/ ,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_keysc_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sh_keysc_isr ; 
 int /*<<< orphan*/  sh_keysc_level_mode (struct sh_keysc_priv*,int /*<<< orphan*/ ) ; 
 TYPE_3__* sh_keysc_mode ; 
 int /*<<< orphan*/  sh_keysc_write (struct sh_keysc_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sh_keysc_probe(struct platform_device *pdev)
{
	struct sh_keysc_priv *priv;
	struct sh_keysc_info *pdata;
	struct resource *res;
	struct input_dev *input;
	int i;
	int irq, error;

	if (!dev_get_platdata(&pdev->dev)) {
		dev_err(&pdev->dev, "no platform data defined\n");
		error = -EINVAL;
		goto err0;
	}

	error = -ENXIO;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "failed to get I/O memory\n");
		goto err0;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		goto err0;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (priv == NULL) {
		dev_err(&pdev->dev, "failed to allocate driver data\n");
		error = -ENOMEM;
		goto err0;
	}

	platform_set_drvdata(pdev, priv);
	memcpy(&priv->pdata, dev_get_platdata(&pdev->dev), sizeof(priv->pdata));
	pdata = &priv->pdata;

	priv->iomem_base = ioremap_nocache(res->start, resource_size(res));
	if (priv->iomem_base == NULL) {
		dev_err(&pdev->dev, "failed to remap I/O memory\n");
		error = -ENXIO;
		goto err1;
	}

	priv->input = input_allocate_device();
	if (!priv->input) {
		dev_err(&pdev->dev, "failed to allocate input device\n");
		error = -ENOMEM;
		goto err2;
	}

	input = priv->input;
	input->evbit[0] = BIT_MASK(EV_KEY);

	input->name = pdev->name;
	input->phys = "sh-keysc-keys/input0";
	input->dev.parent = &pdev->dev;

	input->id.bustype = BUS_HOST;
	input->id.vendor = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	input->keycode = pdata->keycodes;
	input->keycodesize = sizeof(pdata->keycodes[0]);
	input->keycodemax = ARRAY_SIZE(pdata->keycodes);

	error = request_threaded_irq(irq, NULL, sh_keysc_isr, IRQF_ONESHOT,
				     dev_name(&pdev->dev), pdev);
	if (error) {
		dev_err(&pdev->dev, "failed to request IRQ\n");
		goto err3;
	}

	for (i = 0; i < SH_KEYSC_MAXKEYS; i++)
		__set_bit(pdata->keycodes[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	error = input_register_device(input);
	if (error) {
		dev_err(&pdev->dev, "failed to register input device\n");
		goto err4;
	}

	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	sh_keysc_write(priv, KYCR1, (sh_keysc_mode[pdata->mode].kymd << 8) |
		       pdata->scan_timing);
	sh_keysc_level_mode(priv, 0);

	device_init_wakeup(&pdev->dev, 1);

	return 0;

 err4:
	free_irq(irq, pdev);
 err3:
	input_free_device(input);
 err2:
	iounmap(priv->iomem_base);
 err1:
	kfree(priv);
 err0:
	return error;
}