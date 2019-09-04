#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct ndfc_controller {size_t chip_select; scalar_t__ ndfcbase; struct platform_device* ofdev; int /*<<< orphan*/  ndfc_control; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int NDFC_BCFG0 ; 
 scalar_t__ NDFC_CCR ; 
 size_t NDFC_CCR_BS (size_t) ; 
 size_t NDFC_MAX_CS ; 
 size_t be32_to_cpu (int /*<<< orphan*/  const) ; 
 size_t be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct ndfc_controller*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  nand_controller_init (int /*<<< orphan*/ *) ; 
 int ndfc_chip_init (struct ndfc_controller*,int /*<<< orphan*/ ) ; 
 struct ndfc_controller* ndfc_ctrl ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ of_iomap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,size_t) ; 

__attribute__((used)) static int ndfc_probe(struct platform_device *ofdev)
{
	struct ndfc_controller *ndfc;
	const __be32 *reg;
	u32 ccr;
	u32 cs;
	int err, len;

	/* Read the reg property to get the chip select */
	reg = of_get_property(ofdev->dev.of_node, "reg", &len);
	if (reg == NULL || len != 12) {
		dev_err(&ofdev->dev, "unable read reg property (%d)\n", len);
		return -ENOENT;
	}

	cs = be32_to_cpu(reg[0]);
	if (cs >= NDFC_MAX_CS) {
		dev_err(&ofdev->dev, "invalid CS number (%d)\n", cs);
		return -EINVAL;
	}

	ndfc = &ndfc_ctrl[cs];
	ndfc->chip_select = cs;

	nand_controller_init(&ndfc->ndfc_control);
	ndfc->ofdev = ofdev;
	dev_set_drvdata(&ofdev->dev, ndfc);

	ndfc->ndfcbase = of_iomap(ofdev->dev.of_node, 0);
	if (!ndfc->ndfcbase) {
		dev_err(&ofdev->dev, "failed to get memory\n");
		return -EIO;
	}

	ccr = NDFC_CCR_BS(ndfc->chip_select);

	/* It is ok if ccr does not exist - just default to 0 */
	reg = of_get_property(ofdev->dev.of_node, "ccr", NULL);
	if (reg)
		ccr |= be32_to_cpup(reg);

	out_be32(ndfc->ndfcbase + NDFC_CCR, ccr);

	/* Set the bank settings if given */
	reg = of_get_property(ofdev->dev.of_node, "bank-settings", NULL);
	if (reg) {
		int offset = NDFC_BCFG0 + (ndfc->chip_select << 2);
		out_be32(ndfc->ndfcbase + offset, be32_to_cpup(reg));
	}

	err = ndfc_chip_init(ndfc, ofdev->dev.of_node);
	if (err) {
		iounmap(ndfc->ndfcbase);
		return err;
	}

	return 0;
}