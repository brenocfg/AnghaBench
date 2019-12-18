#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int /*<<< orphan*/  algo; int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {int chip_delay; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  select_chip; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmd_ctrl; } ;
struct TYPE_14__ {TYPE_3__ ecc; TYPE_2__ legacy; } ;
struct xway_nand_data {TYPE_4__ chip; int /*<<< orphan*/  nandaddr; } ;
struct resource {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_9__ dev; } ;
struct TYPE_11__ {TYPE_9__* parent; } ;
struct mtd_info {TYPE_1__ dev; } ;

/* Variables and functions */
 int ADDSEL1_MASK (int) ; 
 int ADDSEL1_REGEN ; 
 int BUSCON1_BCGEN_RES ; 
 int BUSCON1_CMULT4 ; 
 int BUSCON1_HOLDC1 ; 
 int BUSCON1_RECOVC1 ; 
 int BUSCON1_SETUP ; 
 int BUSCON1_WAITRDC2 ; 
 int BUSCON1_WAITWRC2 ; 
 int CPHYSADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBU_ADDSEL1 ; 
 int /*<<< orphan*/  EBU_NAND_CON ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTQ_EBU_BUSCON1 ; 
 int NAND_CON_CSMUX ; 
 int NAND_CON_CS_P ; 
 int NAND_CON_IN_CS1 ; 
 int NAND_CON_NANDM ; 
 int NAND_CON_OUT_CS1 ; 
 int NAND_CON_PRE_P ; 
 int NAND_CON_SE_P ; 
 int NAND_CON_WP_P ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_9__*,struct resource*) ; 
 struct xway_nand_data* devm_kzalloc (TYPE_9__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_ebu_w32 (int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (TYPE_4__*) ; 
 int nand_scan (TYPE_4__*,int) ; 
 int /*<<< orphan*/  nand_set_controller_data (TYPE_4__*,struct xway_nand_data*) ; 
 int /*<<< orphan*/  nand_set_flash_node (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (TYPE_4__*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xway_nand_data*) ; 
 int /*<<< orphan*/  xway_cmd_ctrl ; 
 int /*<<< orphan*/  xway_dev_ready ; 
 int /*<<< orphan*/  xway_read_buf ; 
 int /*<<< orphan*/  xway_read_byte ; 
 int /*<<< orphan*/  xway_select_chip ; 
 int /*<<< orphan*/  xway_write_buf ; 

__attribute__((used)) static int xway_nand_probe(struct platform_device *pdev)
{
	struct xway_nand_data *data;
	struct mtd_info *mtd;
	struct resource *res;
	int err;
	u32 cs;
	u32 cs_flag = 0;

	/* Allocate memory for the device structure (and zero it) */
	data = devm_kzalloc(&pdev->dev, sizeof(struct xway_nand_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->nandaddr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(data->nandaddr))
		return PTR_ERR(data->nandaddr);

	nand_set_flash_node(&data->chip, pdev->dev.of_node);
	mtd = nand_to_mtd(&data->chip);
	mtd->dev.parent = &pdev->dev;

	data->chip.legacy.cmd_ctrl = xway_cmd_ctrl;
	data->chip.legacy.dev_ready = xway_dev_ready;
	data->chip.legacy.select_chip = xway_select_chip;
	data->chip.legacy.write_buf = xway_write_buf;
	data->chip.legacy.read_buf = xway_read_buf;
	data->chip.legacy.read_byte = xway_read_byte;
	data->chip.legacy.chip_delay = 30;

	data->chip.ecc.mode = NAND_ECC_SOFT;
	data->chip.ecc.algo = NAND_ECC_HAMMING;

	platform_set_drvdata(pdev, data);
	nand_set_controller_data(&data->chip, data);

	/* load our CS from the DT. Either we find a valid 1 or default to 0 */
	err = of_property_read_u32(pdev->dev.of_node, "lantiq,cs", &cs);
	if (!err && cs == 1)
		cs_flag = NAND_CON_IN_CS1 | NAND_CON_OUT_CS1;

	/* setup the EBU to run in NAND mode on our base addr */
	ltq_ebu_w32(CPHYSADDR(data->nandaddr)
		    | ADDSEL1_MASK(3) | ADDSEL1_REGEN, EBU_ADDSEL1);

	ltq_ebu_w32(BUSCON1_SETUP | BUSCON1_BCGEN_RES | BUSCON1_WAITWRC2
		    | BUSCON1_WAITRDC2 | BUSCON1_HOLDC1 | BUSCON1_RECOVC1
		    | BUSCON1_CMULT4, LTQ_EBU_BUSCON1);

	ltq_ebu_w32(NAND_CON_NANDM | NAND_CON_CSMUX | NAND_CON_CS_P
		    | NAND_CON_SE_P | NAND_CON_WP_P | NAND_CON_PRE_P
		    | cs_flag, EBU_NAND_CON);

	/* Scan to find existence of the device */
	err = nand_scan(&data->chip, 1);
	if (err)
		return err;

	err = mtd_device_register(mtd, NULL, 0);
	if (err)
		nand_release(&data->chip);

	return err;
}