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
struct bma180_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMA250_INT1_DATA_MASK ; 
 int /*<<< orphan*/  BMA250_INT_MAP_REG ; 
 int bma180_chip_init (struct bma180_data*) ; 
 int bma180_set_bits (struct bma180_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bma180_set_bw (struct bma180_data*,int) ; 
 int bma180_set_scale (struct bma180_data*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int bma250_chip_config(struct bma180_data *data)
{
	int ret = bma180_chip_init(data);

	if (ret)
		goto err;
	ret = bma180_set_bw(data, 16); /* 16 Hz */
	if (ret)
		goto err;
	ret = bma180_set_scale(data, 38344); /* 2 G */
	if (ret)
		goto err;
	ret = bma180_set_bits(data, BMA250_INT_MAP_REG,
		BMA250_INT1_DATA_MASK, 1);
	if (ret)
		goto err;

	return 0;

err:
	dev_err(&data->client->dev, "failed to config the chip\n");
	return ret;
}