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
struct device_node {int dummy; } ;
struct denali_controller {int /*<<< orphan*/  dev; } ;
struct denali_chip {int nsels; int /*<<< orphan*/  chip; TYPE_1__* sels; } ;
struct TYPE_2__ {int /*<<< orphan*/  bank; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int denali_chip_init (struct denali_controller*,struct denali_chip*) ; 
 struct denali_chip* devm_kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_set_flash_node (int /*<<< orphan*/ *,struct device_node*) ; 
 int of_property_count_u32_elems (struct device_node*,char*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sels ; 
 int /*<<< orphan*/  struct_size (struct denali_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int denali_dt_chip_init(struct denali_controller *denali,
			       struct device_node *chip_np)
{
	struct denali_chip *dchip;
	u32 bank;
	int nsels, i, ret;

	nsels = of_property_count_u32_elems(chip_np, "reg");
	if (nsels < 0)
		return nsels;

	dchip = devm_kzalloc(denali->dev, struct_size(dchip, sels, nsels),
			     GFP_KERNEL);
	if (!dchip)
		return -ENOMEM;

	dchip->nsels = nsels;

	for (i = 0; i < nsels; i++) {
		ret = of_property_read_u32_index(chip_np, "reg", i, &bank);
		if (ret)
			return ret;

		dchip->sels[i].bank = bank;

		nand_set_flash_node(&dchip->chip, chip_np);
	}

	return denali_chip_init(denali, dchip);
}