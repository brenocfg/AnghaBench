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
struct regmap {int dummy; } ;
struct fimc_dev {int id; struct regmap* sysreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSREG_CAMBLK ; 
 unsigned int SYSREG_CAMBLK_FIFORST_ISP ; 
 unsigned int SYSREG_CAMBLK_ISPWB_FULL_EN ; 
 int /*<<< orphan*/  SYSREG_ISPBLK ; 
 unsigned int SYSREG_ISPBLK_FIFORST_CAM_BLK ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int fimc_hw_camblk_cfg_writeback(struct fimc_dev *fimc)
{
	struct regmap *map = fimc->sysreg;
	unsigned int mask, val, camblk_cfg;
	int ret;

	if (map == NULL)
		return 0;

	ret = regmap_read(map, SYSREG_CAMBLK, &camblk_cfg);
	if (ret < 0 || ((camblk_cfg & 0x00700000) >> 20 != 0x3))
		return ret;

	if (!WARN(fimc->id >= 3, "not supported id: %d\n", fimc->id))
		val = 0x1 << (fimc->id + 20);
	else
		val = 0;

	mask = SYSREG_CAMBLK_FIFORST_ISP | SYSREG_CAMBLK_ISPWB_FULL_EN;
	ret = regmap_update_bits(map, SYSREG_CAMBLK, mask, val);
	if (ret < 0)
		return ret;

	usleep_range(1000, 2000);

	val |= SYSREG_CAMBLK_FIFORST_ISP;
	ret = regmap_update_bits(map, SYSREG_CAMBLK, mask, val);
	if (ret < 0)
		return ret;

	mask = SYSREG_ISPBLK_FIFORST_CAM_BLK;
	ret = regmap_update_bits(map, SYSREG_ISPBLK, mask, ~mask);
	if (ret < 0)
		return ret;

	usleep_range(1000, 2000);

	return regmap_update_bits(map, SYSREG_ISPBLK, mask, mask);
}