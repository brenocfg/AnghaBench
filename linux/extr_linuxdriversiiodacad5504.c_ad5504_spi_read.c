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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct ad5504_state {int /*<<< orphan*/ * data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int AD5504_ADDR (int /*<<< orphan*/ ) ; 
 int AD5504_CMD_READ ; 
 int AD5504_RES_MASK ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int) ; 

__attribute__((used)) static int ad5504_spi_read(struct ad5504_state *st, u8 addr)
{
	int ret;
	struct spi_transfer t = {
	    .tx_buf = &st->data[0],
	    .rx_buf = &st->data[1],
	    .len = 2,
	};

	st->data[0] = cpu_to_be16(AD5504_CMD_READ | AD5504_ADDR(addr));
	ret = spi_sync_transfer(st->spi, &t, 1);
	if (ret < 0)
		return ret;

	return be16_to_cpu(st->data[1]) & AD5504_RES_MASK;
}