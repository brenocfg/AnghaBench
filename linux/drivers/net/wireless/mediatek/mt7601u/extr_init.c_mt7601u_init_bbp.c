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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_MCU_MEMMAP_BBP ; 
 int /*<<< orphan*/  bbp_chip_vals ; 
 int /*<<< orphan*/  bbp_common_vals ; 
 int mt7601u_wait_bbp_ready (struct mt7601u_dev*) ; 
 int mt7601u_write_reg_pairs (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_init_bbp(struct mt7601u_dev *dev)
{
	int ret;

	ret = mt7601u_wait_bbp_ready(dev);
	if (ret)
		return ret;

	ret = mt7601u_write_reg_pairs(dev, MT_MCU_MEMMAP_BBP, bbp_common_vals,
				      ARRAY_SIZE(bbp_common_vals));
	if (ret)
		return ret;

	return mt7601u_write_reg_pairs(dev, MT_MCU_MEMMAP_BBP, bbp_chip_vals,
				       ARRAY_SIZE(bbp_chip_vals));
}