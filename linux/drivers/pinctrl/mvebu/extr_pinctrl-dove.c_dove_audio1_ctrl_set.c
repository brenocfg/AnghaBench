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
struct mvebu_mpp_ctrl_data {int dummy; } ;

/* Variables and functions */
 unsigned int AU1_GPIO_SEL ; 
 int /*<<< orphan*/  AU1_SPDIFO_GPIO_EN ; 
 unsigned long BIT (int) ; 
 int /*<<< orphan*/  GLOBAL_CONFIG_2 ; 
 int /*<<< orphan*/  MPP_GENERAL_CONFIG ; 
 int /*<<< orphan*/  SSP_CTRL_STATUS_1 ; 
 int /*<<< orphan*/  SSP_ON_AU1 ; 
 int /*<<< orphan*/  TWSI_OPTION3_GPIO ; 
 int /*<<< orphan*/  gconfmap ; 
 int /*<<< orphan*/  mpp4_base ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dove_audio1_ctrl_set(struct mvebu_mpp_ctrl_data *data, unsigned pid,
				unsigned long config)
{
	unsigned int mpp4 = readl(mpp4_base);

	mpp4 &= ~AU1_GPIO_SEL;
	if (config & BIT(3))
		mpp4 |= AU1_GPIO_SEL;
	writel(mpp4, mpp4_base);

	regmap_update_bits(gconfmap, SSP_CTRL_STATUS_1,
			   SSP_ON_AU1,
			   (config & BIT(2)) ? SSP_ON_AU1 : 0);
	regmap_update_bits(gconfmap, MPP_GENERAL_CONFIG,
			   AU1_SPDIFO_GPIO_EN,
			   (config & BIT(1)) ? AU1_SPDIFO_GPIO_EN : 0);
	regmap_update_bits(gconfmap, GLOBAL_CONFIG_2,
			   TWSI_OPTION3_GPIO,
			   (config & BIT(0)) ? TWSI_OPTION3_GPIO : 0);

	return 0;
}