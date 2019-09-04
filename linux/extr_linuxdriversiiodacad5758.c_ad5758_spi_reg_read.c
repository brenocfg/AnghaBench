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
struct spi_transfer {int len; int cs_change; void** rx_buf; void** tx_buf; } ;
struct ad5758_state {void** d32; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5758_NOP ; 
 int /*<<< orphan*/  AD5758_TWO_STAGE_READBACK_SELECT ; 
 int AD5758_WR_FLAG_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5758_spi_reg_read(struct ad5758_state *st, unsigned int addr)
{
	struct spi_transfer t[] = {
		{
			.tx_buf = &st->d32[0],
			.len = 4,
			.cs_change = 1,
		}, {
			.tx_buf = &st->d32[1],
			.rx_buf = &st->d32[2],
			.len = 4,
		},
	};
	int ret;

	st->d32[0] = cpu_to_be32(
		(AD5758_WR_FLAG_MSK(AD5758_TWO_STAGE_READBACK_SELECT) << 24) |
		(addr << 8));
	st->d32[1] = cpu_to_be32(AD5758_WR_FLAG_MSK(AD5758_NOP) << 24);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	if (ret < 0)
		return ret;

	return (be32_to_cpu(st->d32[2]) >> 8) & 0xFFFF;
}