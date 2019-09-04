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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {int bits_per_word; int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct ad5791_state {TYPE_1__* data; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {void* d32; int /*<<< orphan*/ * d8; } ;

/* Variables and functions */
 int AD5791_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD5791_ADDR_NOOP ; 
 int AD5791_CMD_READ ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int /*<<< orphan*/  be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5791_spi_read(struct ad5791_state *st, u8 addr, u32 *val)
{
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.bits_per_word = 8,
			.len = 3,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1].d8[1],
			.rx_buf = &st->data[2].d8[1],
			.bits_per_word = 8,
			.len = 3,
		},
	};

	st->data[0].d32 = cpu_to_be32(AD5791_CMD_READ |
			      AD5791_ADDR(addr));
	st->data[1].d32 = cpu_to_be32(AD5791_ADDR(AD5791_ADDR_NOOP));

	ret = spi_sync_transfer(st->spi, xfers, ARRAY_SIZE(xfers));

	*val = be32_to_cpu(st->data[2].d32);

	return ret;
}