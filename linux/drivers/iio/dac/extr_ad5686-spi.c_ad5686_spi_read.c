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
struct spi_transfer {int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_device {int dummy; } ;
struct ad5686_state {TYPE_2__* data; TYPE_1__* chip_info; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {void* d32; int /*<<< orphan*/ * d8; } ;
struct TYPE_3__ {int regmap_type; } ;

/* Variables and functions */
#define  AD5310_REGMAP 130 
#define  AD5683_REGMAP 129 
 int AD5686_ADDR (int /*<<< orphan*/ ) ; 
 int AD5686_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD5686_CMD_NOOP ; 
 int /*<<< orphan*/  AD5686_CMD_READBACK_ENABLE ; 
 int /*<<< orphan*/  AD5686_CMD_READBACK_ENABLE_V2 ; 
#define  AD5686_REGMAP 128 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int spi_sync_transfer (struct spi_device*,struct spi_transfer*,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5686_spi_read(struct ad5686_state *st, u8 addr)
{
	struct spi_transfer t[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.len = 3,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1].d8[1],
			.rx_buf = &st->data[2].d8[1],
			.len = 3,
		},
	};
	struct spi_device *spi = to_spi_device(st->dev);
	u8 cmd = 0;
	int ret;

	switch (st->chip_info->regmap_type) {
	case AD5310_REGMAP:
		return -ENOTSUPP;
	case AD5683_REGMAP:
		cmd = AD5686_CMD_READBACK_ENABLE_V2;
		break;
	case AD5686_REGMAP:
		cmd = AD5686_CMD_READBACK_ENABLE;
		break;
	default:
		return -EINVAL;
	}

	st->data[0].d32 = cpu_to_be32(AD5686_CMD(cmd) |
				      AD5686_ADDR(addr));
	st->data[1].d32 = cpu_to_be32(AD5686_CMD(AD5686_CMD_NOOP));

	ret = spi_sync_transfer(spi, t, ARRAY_SIZE(t));
	if (ret < 0)
		return ret;

	return be32_to_cpu(st->data[2].d32);
}