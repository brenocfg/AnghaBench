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
struct ad7124_state {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int ad_sd_read_reg (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int*) ; 
 int ad_sd_write_reg (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int ad7124_spi_write_mask(struct ad7124_state *st,
				 unsigned int addr,
				 unsigned long mask,
				 unsigned int val,
				 unsigned int bytes)
{
	unsigned int readval;
	int ret;

	ret = ad_sd_read_reg(&st->sd, addr, bytes, &readval);
	if (ret < 0)
		return ret;

	readval &= ~mask;
	readval |= val;

	return ad_sd_write_reg(&st->sd, addr, bytes, readval);
}