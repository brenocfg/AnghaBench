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
struct bma180_data {TYPE_2__* client; TYPE_1__* part_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_reset_mask; int /*<<< orphan*/  int_reset_reg; } ;

/* Variables and functions */
 int bma180_set_bits (struct bma180_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int bma180_reset_intr(struct bma180_data *data)
{
	int ret = bma180_set_bits(data, data->part_info->int_reset_reg,
		data->part_info->int_reset_mask, 1);

	if (ret)
		dev_err(&data->client->dev, "failed to reset interrupt\n");

	return ret;
}