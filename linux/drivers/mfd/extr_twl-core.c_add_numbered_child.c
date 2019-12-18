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
struct twl_client {TYPE_2__* client; } ;
struct resource {int start; int /*<<< orphan*/  flags; } ;
struct device {int /*<<< orphan*/ * parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {struct twl_client* twl_modules; TYPE_1__* twl_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int EPERM ; 
 struct device* ERR_PTR (int) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  device_init_wakeup (struct device*,int) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,void*,unsigned int) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (char const*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int twl_get_last_module () ; 
 TYPE_3__* twl_priv ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct device *
add_numbered_child(unsigned mod_no, const char *name, int num,
		void *pdata, unsigned pdata_len,
		bool can_wakeup, int irq0, int irq1)
{
	struct platform_device	*pdev;
	struct twl_client	*twl;
	int			status, sid;

	if (unlikely(mod_no >= twl_get_last_module())) {
		pr_err("%s: invalid module number %d\n", DRIVER_NAME, mod_no);
		return ERR_PTR(-EPERM);
	}
	sid = twl_priv->twl_map[mod_no].sid;
	twl = &twl_priv->twl_modules[sid];

	pdev = platform_device_alloc(name, num);
	if (!pdev)
		return ERR_PTR(-ENOMEM);

	pdev->dev.parent = &twl->client->dev;

	if (pdata) {
		status = platform_device_add_data(pdev, pdata, pdata_len);
		if (status < 0) {
			dev_dbg(&pdev->dev, "can't add platform_data\n");
			goto put_device;
		}
	}

	if (irq0) {
		struct resource r[2] = {
			{ .start = irq0, .flags = IORESOURCE_IRQ, },
			{ .start = irq1, .flags = IORESOURCE_IRQ, },
		};

		status = platform_device_add_resources(pdev, r, irq1 ? 2 : 1);
		if (status < 0) {
			dev_dbg(&pdev->dev, "can't add irqs\n");
			goto put_device;
		}
	}

	status = platform_device_add(pdev);
	if (status)
		goto put_device;

	device_init_wakeup(&pdev->dev, can_wakeup);

	return &pdev->dev;

put_device:
	platform_device_put(pdev);
	dev_err(&twl->client->dev, "failed to add device %s\n", name);
	return ERR_PTR(status);
}