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
typedef  int u8 ;
typedef  int u64 ;
struct octeon_i2c {scalar_t__ twsi_base; } ;

/* Variables and functions */
 scalar_t__ SW_TWSI (struct octeon_i2c*) ; 
 int SW_TWSI_V ; 
 int __raw_readq (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writeq (int,scalar_t__) ; 

__attribute__((used)) static inline void octeon_i2c_reg_write(struct octeon_i2c *i2c, u64 eop_reg, u8 data)
{
	int tries = 1000;
	u64 tmp;

	__raw_writeq(SW_TWSI_V | eop_reg | data, i2c->twsi_base + SW_TWSI(i2c));
	do {
		tmp = __raw_readq(i2c->twsi_base + SW_TWSI(i2c));
		if (--tries < 0)
			return;
	} while ((tmp & SW_TWSI_V) != 0);
}