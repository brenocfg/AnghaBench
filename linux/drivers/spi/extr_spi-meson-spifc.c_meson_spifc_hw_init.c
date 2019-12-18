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
struct meson_spifc {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SLAVE ; 
 int /*<<< orphan*/  REG_USER ; 
 int /*<<< orphan*/  SLAVE_OP_MODE ; 
 int /*<<< orphan*/  SLAVE_SW_RST ; 
 int /*<<< orphan*/  USER_CMP_MODE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_spifc_hw_init(struct meson_spifc *spifc)
{
	/* reset device */
	regmap_update_bits(spifc->regmap, REG_SLAVE, SLAVE_SW_RST,
			   SLAVE_SW_RST);
	/* disable compatible mode */
	regmap_update_bits(spifc->regmap, REG_USER, USER_CMP_MODE, 0);
	/* set master mode */
	regmap_update_bits(spifc->regmap, REG_SLAVE, SLAVE_OP_MODE, 0);
}