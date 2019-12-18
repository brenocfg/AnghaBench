#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rockchip_iodomain_supply {int idx; struct rockchip_iodomain* iod; } ;
struct rockchip_iodomain {int /*<<< orphan*/  dev; TYPE_1__* soc_data; int /*<<< orphan*/  grf; } ;
struct TYPE_2__ {int /*<<< orphan*/  grf_offset; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MAX_VOLTAGE_1_8 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rockchip_iodomain_write(struct rockchip_iodomain_supply *supply,
				   int uV)
{
	struct rockchip_iodomain *iod = supply->iod;
	u32 val;
	int ret;

	/* set value bit */
	val = (uV > MAX_VOLTAGE_1_8) ? 0 : 1;
	val <<= supply->idx;

	/* apply hiword-mask */
	val |= (BIT(supply->idx) << 16);

	ret = regmap_write(iod->grf, iod->soc_data->grf_offset, val);
	if (ret)
		dev_err(iod->dev, "Couldn't write to GRF\n");

	return ret;
}