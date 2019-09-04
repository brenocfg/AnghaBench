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
typedef  int /*<<< orphan*/  u16 ;
struct spi_transfer {int bits_per_word; int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct ad5761_state {TYPE_1__* data; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {void* d32; int /*<<< orphan*/ * d8; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5761_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD5761_ADDR_NOOP ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int /*<<< orphan*/  be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ad5761_spi_read(struct ad5761_state *st, u8 addr, u16 *val)
{
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.bits_per_word = 8,
			.len = 3,
			.cs_change = true,
		}, {
			.tx_buf = &st->data[1].d8[1],
			.rx_buf = &st->data[2].d8[1],
			.bits_per_word = 8,
			.len = 3,
		},
	};

	st->data[0].d32 = cpu_to_be32(AD5761_ADDR(addr));
	st->data[1].d32 = cpu_to_be32(AD5761_ADDR(AD5761_ADDR_NOOP));

	ret = spi_sync_transfer(st->spi, xfers, ARRAY_SIZE(xfers));

	*val = be32_to_cpu(st->data[2].d32);

	return ret;
}