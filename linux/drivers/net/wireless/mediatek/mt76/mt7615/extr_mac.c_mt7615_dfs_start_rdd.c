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
struct mt7615_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_RX_SEL0 ; 
 int /*<<< orphan*/  RDD_DET_MODE ; 
 int /*<<< orphan*/  RDD_START ; 
 int mt7615_mcu_rdd_cmd (struct mt7615_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt7615_dfs_start_rdd(struct mt7615_dev *dev, int chain)
{
	int err;

	err = mt7615_mcu_rdd_cmd(dev, RDD_START, chain, MT_RX_SEL0, 0);
	if (err < 0)
		return err;

	return mt7615_mcu_rdd_cmd(dev, RDD_DET_MODE, chain,
				  MT_RX_SEL0, 1);
}