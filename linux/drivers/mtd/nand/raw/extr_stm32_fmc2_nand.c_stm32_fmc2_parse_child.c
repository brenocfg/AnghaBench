#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct stm32_fmc2_nand {int ncs; int* cs_used; int /*<<< orphan*/  chip; } ;
struct stm32_fmc2_nfc {int cs_assigned; int /*<<< orphan*/  dev; struct stm32_fmc2_nand nand; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int FMC2_MAX_CE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nand_set_flash_node (int /*<<< orphan*/ *,struct device_node*) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 

__attribute__((used)) static int stm32_fmc2_parse_child(struct stm32_fmc2_nfc *fmc2,
				  struct device_node *dn)
{
	struct stm32_fmc2_nand *nand = &fmc2->nand;
	u32 cs;
	int ret, i;

	if (!of_get_property(dn, "reg", &nand->ncs))
		return -EINVAL;

	nand->ncs /= sizeof(u32);
	if (!nand->ncs) {
		dev_err(fmc2->dev, "invalid reg property size\n");
		return -EINVAL;
	}

	for (i = 0; i < nand->ncs; i++) {
		ret = of_property_read_u32_index(dn, "reg", i, &cs);
		if (ret) {
			dev_err(fmc2->dev, "could not retrieve reg property: %d\n",
				ret);
			return ret;
		}

		if (cs > FMC2_MAX_CE) {
			dev_err(fmc2->dev, "invalid reg value: %d\n", cs);
			return -EINVAL;
		}

		if (fmc2->cs_assigned & BIT(cs)) {
			dev_err(fmc2->dev, "cs already assigned: %d\n", cs);
			return -EINVAL;
		}

		fmc2->cs_assigned |= BIT(cs);
		nand->cs_used[i] = cs;
	}

	nand_set_flash_node(&nand->chip, dn);

	return 0;
}