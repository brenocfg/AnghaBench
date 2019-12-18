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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {char* name; TYPE_1__ dev; } ;
struct net_device {int dummy; } ;
struct mii_bus {char* name; TYPE_1__* parent; struct fec_enet_private* priv; int /*<<< orphan*/  id; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct fec_enet_private {int quirks; scalar_t__ dev_id; int phy_speed; struct mii_bus* mii_bus; scalar_t__ hwp; int /*<<< orphan*/  clk_ipg; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ FEC_MII_SPEED ; 
 int FEC_QUIRK_ENET_MAC ; 
 int FEC_QUIRK_SINGLE_MDIO ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec_enet_mdio_read ; 
 int /*<<< orphan*/  fec_enet_mdio_write ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 scalar_t__ mii_cnt ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int fec_enet_mii_init(struct platform_device *pdev)
{
	static struct mii_bus *fec0_mii_bus;
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct device_node *node;
	int err = -ENXIO;
	u32 mii_speed, holdtime;

	/*
	 * The i.MX28 dual fec interfaces are not equal.
	 * Here are the differences:
	 *
	 *  - fec0 supports MII & RMII modes while fec1 only supports RMII
	 *  - fec0 acts as the 1588 time master while fec1 is slave
	 *  - external phys can only be configured by fec0
	 *
	 * That is to say fec1 can not work independently. It only works
	 * when fec0 is working. The reason behind this design is that the
	 * second interface is added primarily for Switch mode.
	 *
	 * Because of the last point above, both phys are attached on fec0
	 * mdio interface in board design, and need to be configured by
	 * fec0 mii_bus.
	 */
	if ((fep->quirks & FEC_QUIRK_SINGLE_MDIO) && fep->dev_id > 0) {
		/* fec1 uses fec0 mii_bus */
		if (mii_cnt && fec0_mii_bus) {
			fep->mii_bus = fec0_mii_bus;
			mii_cnt++;
			return 0;
		}
		return -ENOENT;
	}

	/*
	 * Set MII speed to 2.5 MHz (= clk_get_rate() / 2 * phy_speed)
	 *
	 * The formula for FEC MDC is 'ref_freq / (MII_SPEED x 2)' while
	 * for ENET-MAC is 'ref_freq / ((MII_SPEED + 1) x 2)'.  The i.MX28
	 * Reference Manual has an error on this, and gets fixed on i.MX6Q
	 * document.
	 */
	mii_speed = DIV_ROUND_UP(clk_get_rate(fep->clk_ipg), 5000000);
	if (fep->quirks & FEC_QUIRK_ENET_MAC)
		mii_speed--;
	if (mii_speed > 63) {
		dev_err(&pdev->dev,
			"fec clock (%lu) too fast to get right mii speed\n",
			clk_get_rate(fep->clk_ipg));
		err = -EINVAL;
		goto err_out;
	}

	/*
	 * The i.MX28 and i.MX6 types have another filed in the MSCR (aka
	 * MII_SPEED) register that defines the MDIO output hold time. Earlier
	 * versions are RAZ there, so just ignore the difference and write the
	 * register always.
	 * The minimal hold time according to IEE802.3 (clause 22) is 10 ns.
	 * HOLDTIME + 1 is the number of clk cycles the fec is holding the
	 * output.
	 * The HOLDTIME bitfield takes values between 0 and 7 (inclusive).
	 * Given that ceil(clkrate / 5000000) <= 64, the calculation for
	 * holdtime cannot result in a value greater than 3.
	 */
	holdtime = DIV_ROUND_UP(clk_get_rate(fep->clk_ipg), 100000000) - 1;

	fep->phy_speed = mii_speed << 1 | holdtime << 8;

	writel(fep->phy_speed, fep->hwp + FEC_MII_SPEED);

	fep->mii_bus = mdiobus_alloc();
	if (fep->mii_bus == NULL) {
		err = -ENOMEM;
		goto err_out;
	}

	fep->mii_bus->name = "fec_enet_mii_bus";
	fep->mii_bus->read = fec_enet_mdio_read;
	fep->mii_bus->write = fec_enet_mdio_write;
	snprintf(fep->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pdev->name, fep->dev_id + 1);
	fep->mii_bus->priv = fep;
	fep->mii_bus->parent = &pdev->dev;

	node = of_get_child_by_name(pdev->dev.of_node, "mdio");
	err = of_mdiobus_register(fep->mii_bus, node);
	of_node_put(node);
	if (err)
		goto err_out_free_mdiobus;

	mii_cnt++;

	/* save fec0 mii_bus */
	if (fep->quirks & FEC_QUIRK_SINGLE_MDIO)
		fec0_mii_bus = fep->mii_bus;

	return 0;

err_out_free_mdiobus:
	mdiobus_free(fep->mii_bus);
err_out:
	return err;
}