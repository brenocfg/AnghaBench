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
typedef  unsigned int uint8_t ;
struct ad7303_state {unsigned int config; int /*<<< orphan*/  data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 unsigned int AD7303_CFG_ADDR_OFFSET ; 
 unsigned int AD7303_CMD_UPDATE_DAC ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad7303_write(struct ad7303_state *st, unsigned int chan,
	uint8_t val)
{
	st->data = cpu_to_be16(AD7303_CMD_UPDATE_DAC |
		(chan << AD7303_CFG_ADDR_OFFSET) |
		st->config | val);

	return spi_write(st->spi, &st->data, sizeof(st->data));
}