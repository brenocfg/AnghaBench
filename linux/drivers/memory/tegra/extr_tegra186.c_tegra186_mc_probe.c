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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ security; scalar_t__ override; } ;
struct tegra_mc_client {int /*<<< orphan*/  name; TYPE_1__ regs; int /*<<< orphan*/  sid; } ;
struct tegra_mc {scalar_t__ regs; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct tegra_mc_client*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra_mc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_mc*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct tegra_mc_client* tegra186_mc_clients ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra186_mc_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct tegra_mc *mc;
	unsigned int i;
	int err = 0;

	mc = devm_kzalloc(&pdev->dev, sizeof(*mc), GFP_KERNEL);
	if (!mc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mc->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mc->regs))
		return PTR_ERR(mc->regs);

	mc->dev = &pdev->dev;

	for (i = 0; i < ARRAY_SIZE(tegra186_mc_clients); i++) {
		const struct tegra_mc_client *client = &tegra186_mc_clients[i];
		u32 override, security;

		override = readl(mc->regs + client->regs.override);
		security = readl(mc->regs + client->regs.security);

		dev_dbg(&pdev->dev, "client %s: override: %x security: %x\n",
			client->name, override, security);

		dev_dbg(&pdev->dev, "setting SID %u for %s\n", client->sid,
			client->name);
		writel(client->sid, mc->regs + client->regs.override);

		override = readl(mc->regs + client->regs.override);
		security = readl(mc->regs + client->regs.security);

		dev_dbg(&pdev->dev, "client %s: override: %x security: %x\n",
			client->name, override, security);
	}

	platform_set_drvdata(pdev, mc);

	return err;
}