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
struct bch_geometry {int gf_len; scalar_t__ ecc_strength; } ;
struct gpmi_nand_data {TYPE_1__* devdata; struct bch_geometry bch_geometry; } ;
struct TYPE_2__ {scalar_t__ bch_max_ecc_strength; } ;

/* Variables and functions */
 scalar_t__ GPMI_IS_MXS (struct gpmi_nand_data*) ; 

__attribute__((used)) static inline bool gpmi_check_ecc(struct gpmi_nand_data *this)
{
	struct bch_geometry *geo = &this->bch_geometry;

	/* Do the sanity check. */
	if (GPMI_IS_MXS(this)) {
		/* The mx23/mx28 only support the GF13. */
		if (geo->gf_len == 14)
			return false;
	}
	return geo->ecc_strength <= this->devdata->bch_max_ecc_strength;
}