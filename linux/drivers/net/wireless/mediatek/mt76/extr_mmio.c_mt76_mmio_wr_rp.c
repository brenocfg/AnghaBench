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
typedef  int /*<<< orphan*/  u32 ;
struct mt76_reg_pair {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_mmio_wr (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt76_mmio_wr_rp(struct mt76_dev *dev, u32 base,
			   const struct mt76_reg_pair *data, int len)
{
	while (len > 0) {
		mt76_mmio_wr(dev, data->reg, data->value);
		data++;
		len--;
	}

	return 0;
}