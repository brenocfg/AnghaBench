#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {int (* data ) (struct device_node*) ;} ;
struct mii_bus {char* name; TYPE_1__* parent; int /*<<< orphan*/  phy_mask; int /*<<< orphan*/  id; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; struct fec_info* priv; } ;
struct fec_info {int mii_speed; TYPE_2__* fecp; } ;
struct TYPE_7__ {int /*<<< orphan*/  fec_mii_speed; int /*<<< orphan*/  fec_ievent; int /*<<< orphan*/  fec_ecntrl; int /*<<< orphan*/  fec_r_cntrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FEC_ECNTRL_ETHER_EN ; 
 int FEC_ECNTRL_PINMUX ; 
 int /*<<< orphan*/  FEC_ENET_MII ; 
 int FEC_RCNTRL_MII_MODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  clrsetbits_be32 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fs_enet_fec_mii_read ; 
 int /*<<< orphan*/  fs_enet_fec_mii_write ; 
 int /*<<< orphan*/  fs_enet_mdio_fec_match ; 
 TYPE_2__* ioremap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct fec_info*) ; 
 struct fec_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mii_bus* mdiobus_alloc () ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int of_mdiobus_register (struct mii_bus*,struct device_node*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mii_bus*) ; 
 int /*<<< orphan*/  ppc_proc_freq ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int fs_enet_mdio_probe(struct platform_device *ofdev)
{
	const struct of_device_id *match;
	struct resource res;
	struct mii_bus *new_bus;
	struct fec_info *fec;
	int (*get_bus_freq)(struct device_node *);
	int ret = -ENOMEM, clock, speed;

	match = of_match_device(fs_enet_mdio_fec_match, &ofdev->dev);
	if (!match)
		return -EINVAL;
	get_bus_freq = match->data;

	new_bus = mdiobus_alloc();
	if (!new_bus)
		goto out;

	fec = kzalloc(sizeof(struct fec_info), GFP_KERNEL);
	if (!fec)
		goto out_mii;

	new_bus->priv = fec;
	new_bus->name = "FEC MII Bus";
	new_bus->read = &fs_enet_fec_mii_read;
	new_bus->write = &fs_enet_fec_mii_write;

	ret = of_address_to_resource(ofdev->dev.of_node, 0, &res);
	if (ret)
		goto out_res;

	snprintf(new_bus->id, MII_BUS_ID_SIZE, "%x", res.start);

	fec->fecp = ioremap(res.start, resource_size(&res));
	if (!fec->fecp) {
		ret = -ENOMEM;
		goto out_fec;
	}

	if (get_bus_freq) {
		clock = get_bus_freq(ofdev->dev.of_node);
		if (!clock) {
			/* Use maximum divider if clock is unknown */
			dev_warn(&ofdev->dev, "could not determine IPS clock\n");
			clock = 0x3F * 5000000;
		}
	} else
		clock = ppc_proc_freq;

	/*
	 * Scale for a MII clock <= 2.5 MHz
	 * Note that only 6 bits (25:30) are available for MII speed.
	 */
	speed = (clock + 4999999) / 5000000;
	if (speed > 0x3F) {
		speed = 0x3F;
		dev_err(&ofdev->dev,
			"MII clock (%d Hz) exceeds max (2.5 MHz)\n",
			clock / speed);
	}

	fec->mii_speed = speed << 1;

	setbits32(&fec->fecp->fec_r_cntrl, FEC_RCNTRL_MII_MODE);
	setbits32(&fec->fecp->fec_ecntrl, FEC_ECNTRL_PINMUX |
	                                  FEC_ECNTRL_ETHER_EN);
	out_be32(&fec->fecp->fec_ievent, FEC_ENET_MII);
	clrsetbits_be32(&fec->fecp->fec_mii_speed, 0x7E, fec->mii_speed);

	new_bus->phy_mask = ~0;

	new_bus->parent = &ofdev->dev;
	platform_set_drvdata(ofdev, new_bus);

	ret = of_mdiobus_register(new_bus, ofdev->dev.of_node);
	if (ret)
		goto out_unmap_regs;

	return 0;

out_unmap_regs:
	iounmap(fec->fecp);
out_res:
out_fec:
	kfree(fec);
out_mii:
	mdiobus_free(new_bus);
out:
	return ret;
}