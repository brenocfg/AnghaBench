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
typedef  int /*<<< orphan*/  const u32 ;
struct malidp_hw_device {TYPE_2__* hw; } ;
struct TYPE_3__ {scalar_t__ coeffs_base; } ;
struct TYPE_4__ {TYPE_1__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  const GENMASK (int,int) ; 
 int MALIDP_COEFFTAB_NUM_COEFFS ; 
 scalar_t__ MALIDP_COEF_TABLE_ADDR ; 
 scalar_t__ MALIDP_COEF_TABLE_DATA ; 
 int /*<<< orphan*/  malidp_hw_write (struct malidp_hw_device*,int /*<<< orphan*/  const,scalar_t__) ; 

__attribute__((used)) static void malidp_write_gamma_table(struct malidp_hw_device *hwdev,
				     u32 data[MALIDP_COEFFTAB_NUM_COEFFS])
{
	int i;
	/* Update all channels with a single gamma curve. */
	const u32 gamma_write_mask = GENMASK(18, 16);
	/*
	 * Always write an entire table, so the address field in
	 * DE_COEFFTAB_ADDR is 0 and we can use the gamma_write_mask bitmask
	 * directly.
	 */
	malidp_hw_write(hwdev, gamma_write_mask,
			hwdev->hw->map.coeffs_base + MALIDP_COEF_TABLE_ADDR);
	for (i = 0; i < MALIDP_COEFFTAB_NUM_COEFFS; ++i)
		malidp_hw_write(hwdev, data[i],
				hwdev->hw->map.coeffs_base +
				MALIDP_COEF_TABLE_DATA);
}