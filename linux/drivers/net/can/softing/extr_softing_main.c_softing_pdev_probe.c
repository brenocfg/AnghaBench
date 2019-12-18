#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct softing_priv {int index; } ;
struct softing_platform_data {int nbus; int /*<<< orphan*/  name; int /*<<< orphan*/  freq; } ;
struct TYPE_10__ {int /*<<< orphan*/ * chip; int /*<<< orphan*/  freq; } ;
struct TYPE_9__ {int /*<<< orphan*/  nr; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct softing {int /*<<< orphan*/  dpram; struct net_device** net; struct softing_platform_data const* pdat; struct platform_device* pdev; TYPE_3__ id; TYPE_2__ irq; int /*<<< orphan*/  dpram_size; int /*<<< orphan*/  dpram_phys; int /*<<< orphan*/  spin; TYPE_1__ fw; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_4__ dev; } ;
struct net_device {int dev_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct net_device**) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_alert (TYPE_4__*,char*,...) ; 
 struct softing_platform_data* dev_get_platdata (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct softing*) ; 
 struct softing* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct softing_priv* netdev_priv (struct net_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct softing*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int softing_card_boot (struct softing*) ; 
 int /*<<< orphan*/  softing_card_shutdown (struct softing*) ; 
 int /*<<< orphan*/  softing_netdev_cleanup (struct net_device*) ; 
 struct net_device* softing_netdev_create (struct softing*,int /*<<< orphan*/ ) ; 
 int softing_netdev_register (struct net_device*) ; 
 int /*<<< orphan*/  softing_pdev_group ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int softing_pdev_probe(struct platform_device *pdev)
{
	const struct softing_platform_data *pdat = dev_get_platdata(&pdev->dev);
	struct softing *card;
	struct net_device *netdev;
	struct softing_priv *priv;
	struct resource *pres;
	int ret;
	int j;

	if (!pdat) {
		dev_warn(&pdev->dev, "no platform data\n");
		return -EINVAL;
	}
	if (pdat->nbus > ARRAY_SIZE(card->net)) {
		dev_warn(&pdev->dev, "%u nets??\n", pdat->nbus);
		return -EINVAL;
	}

	card = kzalloc(sizeof(*card), GFP_KERNEL);
	if (!card)
		return -ENOMEM;
	card->pdat = pdat;
	card->pdev = pdev;
	platform_set_drvdata(pdev, card);
	mutex_init(&card->fw.lock);
	spin_lock_init(&card->spin);

	ret = -EINVAL;
	pres = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!pres)
		goto platform_resource_failed;
	card->dpram_phys = pres->start;
	card->dpram_size = resource_size(pres);
	card->dpram = ioremap_nocache(card->dpram_phys, card->dpram_size);
	if (!card->dpram) {
		dev_alert(&card->pdev->dev, "dpram ioremap failed\n");
		goto ioremap_failed;
	}

	pres = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (pres)
		card->irq.nr = pres->start;

	/* reset card */
	ret = softing_card_boot(card);
	if (ret < 0) {
		dev_alert(&pdev->dev, "failed to boot\n");
		goto boot_failed;
	}

	/* only now, the chip's are known */
	card->id.freq = card->pdat->freq;

	ret = sysfs_create_group(&pdev->dev.kobj, &softing_pdev_group);
	if (ret < 0) {
		dev_alert(&card->pdev->dev, "sysfs failed\n");
		goto sysfs_failed;
	}

	for (j = 0; j < ARRAY_SIZE(card->net); ++j) {
		card->net[j] = netdev =
			softing_netdev_create(card, card->id.chip[j]);
		if (!netdev) {
			dev_alert(&pdev->dev, "failed to make can[%i]", j);
			ret = -ENOMEM;
			goto netdev_failed;
		}
		netdev->dev_id = j;
		priv = netdev_priv(card->net[j]);
		priv->index = j;
		ret = softing_netdev_register(netdev);
		if (ret) {
			free_candev(netdev);
			card->net[j] = NULL;
			dev_alert(&card->pdev->dev,
					"failed to register can[%i]\n", j);
			goto netdev_failed;
		}
	}
	dev_info(&card->pdev->dev, "%s ready.\n", card->pdat->name);
	return 0;

netdev_failed:
	for (j = 0; j < ARRAY_SIZE(card->net); ++j) {
		if (!card->net[j])
			continue;
		softing_netdev_cleanup(card->net[j]);
	}
	sysfs_remove_group(&pdev->dev.kobj, &softing_pdev_group);
sysfs_failed:
	softing_card_shutdown(card);
boot_failed:
	iounmap(card->dpram);
ioremap_failed:
platform_resource_failed:
	kfree(card);
	return ret;
}