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
typedef  scalar_t__ u32 ;
struct reset_controller_dev {int dummy; } ;
struct aspeed_reset {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 scalar_t__ ASPEED_RESET2_OFFSET ; 
 scalar_t__ ASPEED_RESET_CTRL ; 
 scalar_t__ ASPEED_RESET_CTRL2 ; 
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 scalar_t__* aspeed_resets ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aspeed_reset* to_aspeed_reset (struct reset_controller_dev*) ; 

__attribute__((used)) static int aspeed_reset_deassert(struct reset_controller_dev *rcdev,
				 unsigned long id)
{
	struct aspeed_reset *ar = to_aspeed_reset(rcdev);
	u32 reg = ASPEED_RESET_CTRL;
	u32 bit = aspeed_resets[id];

	if (bit >= ASPEED_RESET2_OFFSET) {
		bit -= ASPEED_RESET2_OFFSET;
		reg = ASPEED_RESET_CTRL2;
	}

	return regmap_update_bits(ar->map, reg, BIT(bit), 0);
}