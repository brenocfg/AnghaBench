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
struct reg_table {int /*<<< orphan*/  n; int /*<<< orphan*/  regs; } ;
struct mt7601u_dev {int temp_mode; size_t bw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MCU_MEMMAP_BBP ; 
 struct reg_table** bbp_mode_table ; 
 int mt7601u_write_reg_pairs (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_temp_mode (struct mt7601u_dev*,int) ; 

__attribute__((used)) static int mt7601u_bbp_temp(struct mt7601u_dev *dev, int mode, const char *name)
{
	const struct reg_table *t;
	int ret;

	if (dev->temp_mode == mode)
		return 0;

	dev->temp_mode = mode;
	trace_temp_mode(dev, mode);

	t = bbp_mode_table[dev->temp_mode];
	ret = mt7601u_write_reg_pairs(dev, MT_MCU_MEMMAP_BBP,
				      t[2].regs, t[2].n);
	if (ret)
		return ret;

	return mt7601u_write_reg_pairs(dev, MT_MCU_MEMMAP_BBP,
				       t[dev->bw].regs, t[dev->bw].n);
}