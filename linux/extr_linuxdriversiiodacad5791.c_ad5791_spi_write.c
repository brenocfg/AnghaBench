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
typedef  int u32 ;
struct ad5791_state {TYPE_1__* data; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * d8; int /*<<< orphan*/  d32; } ;

/* Variables and functions */
 int AD5791_ADDR (int /*<<< orphan*/ ) ; 
 int AD5791_CMD_WRITE ; 
 int AD5791_DAC_MASK ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad5791_spi_write(struct ad5791_state *st, u8 addr, u32 val)
{
	st->data[0].d32 = cpu_to_be32(AD5791_CMD_WRITE |
			      AD5791_ADDR(addr) |
			      (val & AD5791_DAC_MASK));

	return spi_write(st->spi, &st->data[0].d8[1], 3);
}