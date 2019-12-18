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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct nand_chip {TYPE_3__* controller; TYPE_2__ ecc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct mtd_info {TYPE_1__ dev; } ;
struct gpio_descs {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
struct ams_delta_nand {int data_in; TYPE_3__ base; struct gpio_descs* data_gpiods; struct gpio_descs* gpiod_cle; struct gpio_descs* gpiod_ale; struct gpio_descs* gpiod_nwe; struct gpio_descs* gpiod_nre; struct gpio_descs* gpiod_nce; struct gpio_descs* gpiod_nwp; struct gpio_descs* gpiod_rdy; struct nand_chip nand_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_descs*) ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int PTR_ERR (struct gpio_descs*) ; 
 int /*<<< orphan*/  ams_delta_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct gpio_descs* devm_gpiod_get_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct gpio_descs* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ams_delta_nand* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_controller_init (TYPE_3__*) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (struct nand_chip*,struct ams_delta_nand*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  partition_info ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ams_delta_nand*) ; 

__attribute__((used)) static int ams_delta_init(struct platform_device *pdev)
{
	struct ams_delta_nand *priv;
	struct nand_chip *this;
	struct mtd_info *mtd;
	struct gpio_descs *data_gpiods;
	int err = 0;

	/* Allocate memory for MTD device structure and private data */
	priv = devm_kzalloc(&pdev->dev, sizeof(struct ams_delta_nand),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	this = &priv->nand_chip;

	mtd = nand_to_mtd(this);
	mtd->dev.parent = &pdev->dev;

	nand_set_controller_data(this, priv);

	priv->gpiod_rdy = devm_gpiod_get_optional(&pdev->dev, "rdy", GPIOD_IN);
	if (IS_ERR(priv->gpiod_rdy)) {
		err = PTR_ERR(priv->gpiod_rdy);
		dev_warn(&pdev->dev, "RDY GPIO request failed (%d)\n", err);
		return err;
	}

	this->ecc.mode = NAND_ECC_SOFT;
	this->ecc.algo = NAND_ECC_HAMMING;

	platform_set_drvdata(pdev, priv);

	/* Set chip enabled, but  */
	priv->gpiod_nwp = devm_gpiod_get(&pdev->dev, "nwp", GPIOD_OUT_HIGH);
	if (IS_ERR(priv->gpiod_nwp)) {
		err = PTR_ERR(priv->gpiod_nwp);
		dev_err(&pdev->dev, "NWP GPIO request failed (%d)\n", err);
		return err;
	}

	priv->gpiod_nce = devm_gpiod_get(&pdev->dev, "nce", GPIOD_OUT_HIGH);
	if (IS_ERR(priv->gpiod_nce)) {
		err = PTR_ERR(priv->gpiod_nce);
		dev_err(&pdev->dev, "NCE GPIO request failed (%d)\n", err);
		return err;
	}

	priv->gpiod_nre = devm_gpiod_get(&pdev->dev, "nre", GPIOD_OUT_HIGH);
	if (IS_ERR(priv->gpiod_nre)) {
		err = PTR_ERR(priv->gpiod_nre);
		dev_err(&pdev->dev, "NRE GPIO request failed (%d)\n", err);
		return err;
	}

	priv->gpiod_nwe = devm_gpiod_get(&pdev->dev, "nwe", GPIOD_OUT_HIGH);
	if (IS_ERR(priv->gpiod_nwe)) {
		err = PTR_ERR(priv->gpiod_nwe);
		dev_err(&pdev->dev, "NWE GPIO request failed (%d)\n", err);
		return err;
	}

	priv->gpiod_ale = devm_gpiod_get(&pdev->dev, "ale", GPIOD_OUT_LOW);
	if (IS_ERR(priv->gpiod_ale)) {
		err = PTR_ERR(priv->gpiod_ale);
		dev_err(&pdev->dev, "ALE GPIO request failed (%d)\n", err);
		return err;
	}

	priv->gpiod_cle = devm_gpiod_get(&pdev->dev, "cle", GPIOD_OUT_LOW);
	if (IS_ERR(priv->gpiod_cle)) {
		err = PTR_ERR(priv->gpiod_cle);
		dev_err(&pdev->dev, "CLE GPIO request failed (%d)\n", err);
		return err;
	}

	/* Request array of data pins, initialize them as input */
	data_gpiods = devm_gpiod_get_array(&pdev->dev, "data", GPIOD_IN);
	if (IS_ERR(data_gpiods)) {
		err = PTR_ERR(data_gpiods);
		dev_err(&pdev->dev, "data GPIO request failed: %d\n", err);
		return err;
	}
	priv->data_gpiods = data_gpiods;
	priv->data_in = true;

	/* Initialize the NAND controller object embedded in ams_delta_nand. */
	priv->base.ops = &ams_delta_ops;
	nand_controller_init(&priv->base);
	this->controller = &priv->base;

	/* Scan to find existence of the device */
	err = nand_scan(this, 1);
	if (err)
		return err;

	/* Register the partitions */
	err = mtd_device_register(mtd, partition_info,
				  ARRAY_SIZE(partition_info));
	if (err)
		goto err_nand_cleanup;

	return 0;

err_nand_cleanup:
	nand_cleanup(this);

	return err;
}