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
struct bma180_data {int pmode; TYPE_2__* client; TYPE_1__* part_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  power_mask; int /*<<< orphan*/  power_reg; int /*<<< orphan*/  lowpower_val; } ;

/* Variables and functions */
 int bma180_set_bits (struct bma180_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int bma180_set_pmode(struct bma180_data *data, bool mode)
{
	u8 reg_val = mode ? data->part_info->lowpower_val : 0;
	int ret = bma180_set_bits(data, data->part_info->power_reg,
		data->part_info->power_mask, reg_val);

	if (ret) {
		dev_err(&data->client->dev, "failed to set power mode\n");
		return ret;
	}
	data->pmode = mode;

	return 0;
}