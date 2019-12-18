#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; scalar_t__ end; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {char* name; int id; TYPE_2__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct mii_bus {char* name; TYPE_1__ dev; int /*<<< orphan*/  phy_mask; int /*<<< orphan*/  write; int /*<<< orphan*/  read; TYPE_2__* parent; int /*<<< orphan*/  id; struct iproc_mdiomux_desc* priv; } ;
struct iproc_mdiomux_desc {int /*<<< orphan*/ * core_clk; TYPE_2__* dev; struct mii_bus* mii_bus; int /*<<< orphan*/  mux_handle; int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ MDIO_REG_ADDR_SPACE_SIZE ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct iproc_mdiomux_desc* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct mii_bus* devm_mdiobus_alloc (TYPE_2__*) ; 
 int /*<<< orphan*/  iproc_mdiomux_read ; 
 int /*<<< orphan*/  iproc_mdiomux_write ; 
 int mdio_mux_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct iproc_mdiomux_desc*,struct mii_bus*) ; 
 int /*<<< orphan*/  mdio_mux_iproc_config (struct iproc_mdiomux_desc*) ; 
 int /*<<< orphan*/  mdio_mux_iproc_switch_fn ; 
 int mdiobus_register (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iproc_mdiomux_desc*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int mdio_mux_iproc_probe(struct platform_device *pdev)
{
	struct iproc_mdiomux_desc *md;
	struct mii_bus *bus;
	struct resource *res;
	int rc;

	md = devm_kzalloc(&pdev->dev, sizeof(*md), GFP_KERNEL);
	if (!md)
		return -ENOMEM;
	md->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res->start & 0xfff) {
		/* For backward compatibility in case the
		 * base address is specified with an offset.
		 */
		dev_info(&pdev->dev, "fix base address in dt-blob\n");
		res->start &= ~0xfff;
		res->end = res->start + MDIO_REG_ADDR_SPACE_SIZE - 1;
	}
	md->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(md->base)) {
		dev_err(&pdev->dev, "failed to ioremap register\n");
		return PTR_ERR(md->base);
	}

	md->mii_bus = devm_mdiobus_alloc(&pdev->dev);
	if (!md->mii_bus) {
		dev_err(&pdev->dev, "mdiomux bus alloc failed\n");
		return -ENOMEM;
	}

	md->core_clk = devm_clk_get(&pdev->dev, NULL);
	if (md->core_clk == ERR_PTR(-ENOENT) ||
	    md->core_clk == ERR_PTR(-EINVAL))
		md->core_clk = NULL;
	else if (IS_ERR(md->core_clk))
		return PTR_ERR(md->core_clk);

	rc = clk_prepare_enable(md->core_clk);
	if (rc) {
		dev_err(&pdev->dev, "failed to enable core clk\n");
		return rc;
	}

	bus = md->mii_bus;
	bus->priv = md;
	bus->name = "iProc MDIO mux bus";
	snprintf(bus->id, MII_BUS_ID_SIZE, "%s-%d", pdev->name, pdev->id);
	bus->parent = &pdev->dev;
	bus->read = iproc_mdiomux_read;
	bus->write = iproc_mdiomux_write;

	bus->phy_mask = ~0;
	bus->dev.of_node = pdev->dev.of_node;
	rc = mdiobus_register(bus);
	if (rc) {
		dev_err(&pdev->dev, "mdiomux registration failed\n");
		goto out_clk;
	}

	platform_set_drvdata(pdev, md);

	rc = mdio_mux_init(md->dev, md->dev->of_node, mdio_mux_iproc_switch_fn,
			   &md->mux_handle, md, md->mii_bus);
	if (rc) {
		dev_info(md->dev, "mdiomux initialization failed\n");
		goto out_register;
	}

	mdio_mux_iproc_config(md);

	dev_info(md->dev, "iProc mdiomux registered\n");
	return 0;

out_register:
	mdiobus_unregister(bus);
out_clk:
	clk_disable_unprepare(md->core_clk);
	return rc;
}