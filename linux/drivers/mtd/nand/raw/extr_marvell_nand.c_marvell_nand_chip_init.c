#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pxa3xx_nand_platform_data {int /*<<< orphan*/  nr_parts; int /*<<< orphan*/ * parts; } ;
struct TYPE_8__ {int /*<<< orphan*/  mode; } ;
struct nand_chip {int /*<<< orphan*/  options; TYPE_4__ ecc; int /*<<< orphan*/ * controller; } ;
struct TYPE_7__ {struct device* parent; } ;
struct mtd_info {TYPE_3__ dev; } ;
struct marvell_nfc {int /*<<< orphan*/  chips; scalar_t__ regs; int /*<<< orphan*/  controller; TYPE_1__* caps; int /*<<< orphan*/  assigned_cs; } ;
struct marvell_nand_chip {int nsels; int selected_die; int /*<<< orphan*/  node; void* ndtr1; void* ndtr0; struct nand_chip chip; TYPE_2__* sels; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int cs; int rb; int /*<<< orphan*/  ndcb0_csel; } ;
struct TYPE_5__ {int max_cs_nb; int max_rb_nb; scalar_t__ legacy_of_bindings; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_BUSWIDTH_AUTO ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  NAND_KEEP_TIMINGS ; 
 int /*<<< orphan*/  NDCB0_CSEL ; 
 scalar_t__ NDTR0 ; 
 scalar_t__ NDTR1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct pxa3xx_nand_platform_data* dev_get_platdata (struct device*) ; 
 struct marvell_nand_chip* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (struct nand_chip*) ; 
 int nand_scan (struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_set_flash_node (struct nand_chip*,struct device_node*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int of_property_count_elems_of_size (struct device_node*,char*,int) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 void* readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sels ; 
 int /*<<< orphan*/  struct_size (struct marvell_nand_chip*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int marvell_nand_chip_init(struct device *dev, struct marvell_nfc *nfc,
				  struct device_node *np)
{
	struct pxa3xx_nand_platform_data *pdata = dev_get_platdata(dev);
	struct marvell_nand_chip *marvell_nand;
	struct mtd_info *mtd;
	struct nand_chip *chip;
	int nsels, ret, i;
	u32 cs, rb;

	/*
	 * The legacy "num-cs" property indicates the number of CS on the only
	 * chip connected to the controller (legacy bindings does not support
	 * more than one chip). The CS and RB pins are always the #0.
	 *
	 * When not using legacy bindings, a couple of "reg" and "nand-rb"
	 * properties must be filled. For each chip, expressed as a subnode,
	 * "reg" points to the CS lines and "nand-rb" to the RB line.
	 */
	if (pdata || nfc->caps->legacy_of_bindings) {
		nsels = 1;
	} else {
		nsels = of_property_count_elems_of_size(np, "reg", sizeof(u32));
		if (nsels <= 0) {
			dev_err(dev, "missing/invalid reg property\n");
			return -EINVAL;
		}
	}

	/* Alloc the nand chip structure */
	marvell_nand = devm_kzalloc(dev,
				    struct_size(marvell_nand, sels, nsels),
				    GFP_KERNEL);
	if (!marvell_nand) {
		dev_err(dev, "could not allocate chip structure\n");
		return -ENOMEM;
	}

	marvell_nand->nsels = nsels;
	marvell_nand->selected_die = -1;

	for (i = 0; i < nsels; i++) {
		if (pdata || nfc->caps->legacy_of_bindings) {
			/*
			 * Legacy bindings use the CS lines in natural
			 * order (0, 1, ...)
			 */
			cs = i;
		} else {
			/* Retrieve CS id */
			ret = of_property_read_u32_index(np, "reg", i, &cs);
			if (ret) {
				dev_err(dev, "could not retrieve reg property: %d\n",
					ret);
				return ret;
			}
		}

		if (cs >= nfc->caps->max_cs_nb) {
			dev_err(dev, "invalid reg value: %u (max CS = %d)\n",
				cs, nfc->caps->max_cs_nb);
			return -EINVAL;
		}

		if (test_and_set_bit(cs, &nfc->assigned_cs)) {
			dev_err(dev, "CS %d already assigned\n", cs);
			return -EINVAL;
		}

		/*
		 * The cs variable represents the chip select id, which must be
		 * converted in bit fields for NDCB0 and NDCB2 to select the
		 * right chip. Unfortunately, due to a lack of information on
		 * the subject and incoherent documentation, the user should not
		 * use CS1 and CS3 at all as asserting them is not supported in
		 * a reliable way (due to multiplexing inside ADDR5 field).
		 */
		marvell_nand->sels[i].cs = cs;
		switch (cs) {
		case 0:
		case 2:
			marvell_nand->sels[i].ndcb0_csel = 0;
			break;
		case 1:
		case 3:
			marvell_nand->sels[i].ndcb0_csel = NDCB0_CSEL;
			break;
		default:
			return -EINVAL;
		}

		/* Retrieve RB id */
		if (pdata || nfc->caps->legacy_of_bindings) {
			/* Legacy bindings always use RB #0 */
			rb = 0;
		} else {
			ret = of_property_read_u32_index(np, "nand-rb", i,
							 &rb);
			if (ret) {
				dev_err(dev,
					"could not retrieve RB property: %d\n",
					ret);
				return ret;
			}
		}

		if (rb >= nfc->caps->max_rb_nb) {
			dev_err(dev, "invalid reg value: %u (max RB = %d)\n",
				rb, nfc->caps->max_rb_nb);
			return -EINVAL;
		}

		marvell_nand->sels[i].rb = rb;
	}

	chip = &marvell_nand->chip;
	chip->controller = &nfc->controller;
	nand_set_flash_node(chip, np);

	if (!of_property_read_bool(np, "marvell,nand-keep-config"))
		chip->options |= NAND_KEEP_TIMINGS;

	mtd = nand_to_mtd(chip);
	mtd->dev.parent = dev;

	/*
	 * Default to HW ECC engine mode. If the nand-ecc-mode property is given
	 * in the DT node, this entry will be overwritten in nand_scan_ident().
	 */
	chip->ecc.mode = NAND_ECC_HW;

	/*
	 * Save a reference value for timing registers before
	 * ->setup_data_interface() is called.
	 */
	marvell_nand->ndtr0 = readl_relaxed(nfc->regs + NDTR0);
	marvell_nand->ndtr1 = readl_relaxed(nfc->regs + NDTR1);

	chip->options |= NAND_BUSWIDTH_AUTO;

	ret = nand_scan(chip, marvell_nand->nsels);
	if (ret) {
		dev_err(dev, "could not scan the nand chip\n");
		return ret;
	}

	if (pdata)
		/* Legacy bindings support only one chip */
		ret = mtd_device_register(mtd, pdata->parts, pdata->nr_parts);
	else
		ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(dev, "failed to register mtd device: %d\n", ret);
		nand_release(chip);
		return ret;
	}

	list_add_tail(&marvell_nand->node, &nfc->chips);

	return 0;
}