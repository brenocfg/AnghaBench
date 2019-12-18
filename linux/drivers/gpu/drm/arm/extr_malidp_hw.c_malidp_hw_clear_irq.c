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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct malidp_hw_device {TYPE_2__* hw; } ;
struct TYPE_3__ {int features; } ;
struct TYPE_4__ {TYPE_1__ map; } ;

/* Variables and functions */
 int MALIDP_REGMAP_HAS_CLEARIRQ ; 
 scalar_t__ MALIDP_REG_CLEARIRQ ; 
 scalar_t__ MALIDP_REG_STATUS ; 
 scalar_t__ malidp_get_block_base (struct malidp_hw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_write (struct malidp_hw_device*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void malidp_hw_clear_irq(struct malidp_hw_device *hwdev, u8 block, u32 irq)
{
	u32 base = malidp_get_block_base(hwdev, block);

	if (hwdev->hw->map.features & MALIDP_REGMAP_HAS_CLEARIRQ)
		malidp_hw_write(hwdev, irq, base + MALIDP_REG_CLEARIRQ);
	else
		malidp_hw_write(hwdev, irq, base + MALIDP_REG_STATUS);
}