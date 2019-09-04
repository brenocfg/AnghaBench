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
typedef  int u16 ;
struct ad5504_state {int /*<<< orphan*/ * data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int AD5504_ADDR (int /*<<< orphan*/ ) ; 
 int AD5504_CMD_WRITE ; 
 int AD5504_RES_MASK ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad5504_spi_write(struct ad5504_state *st, u8 addr, u16 val)
{
	st->data[0] = cpu_to_be16(AD5504_CMD_WRITE | AD5504_ADDR(addr) |
			      (val & AD5504_RES_MASK));

	return spi_write(st->spi, &st->data[0], 2);
}