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
struct ad5758_state {int /*<<< orphan*/ * d32; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int AD5758_WR_FLAG_MSK (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad5758_spi_reg_write(struct ad5758_state *st,
				unsigned int addr,
				unsigned int val)
{
	st->d32[0] = cpu_to_be32((AD5758_WR_FLAG_MSK(addr) << 24) |
				 ((val & 0xFFFF) << 8));

	return spi_write(st->spi, &st->d32[0], sizeof(st->d32[0]));
}