#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ strength; scalar_t__ size; } ;
struct nand_chip {scalar_t__ ecc_strength_ds; scalar_t__ ecc_step_ds; TYPE_2__ ecc; } ;
struct gpmi_nand_data {TYPE_1__* dev; struct nand_chip nand; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ legacy_set_geometry (struct gpmi_nand_data*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int set_geometry_by_ecc_info (struct gpmi_nand_data*,scalar_t__,scalar_t__) ; 

int common_nfc_set_geometry(struct gpmi_nand_data *this)
{
	struct nand_chip *chip = &this->nand;

	if (chip->ecc.strength > 0 && chip->ecc.size > 0)
		return set_geometry_by_ecc_info(this, chip->ecc.strength,
						chip->ecc.size);

	if ((of_property_read_bool(this->dev->of_node, "fsl,use-minimum-ecc"))
				|| legacy_set_geometry(this)) {
		if (!(chip->ecc_strength_ds > 0 && chip->ecc_step_ds > 0))
			return -EINVAL;

		return set_geometry_by_ecc_info(this, chip->ecc_strength_ds,
						chip->ecc_step_ds);
	}

	return 0;
}