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
typedef  int u64 ;
struct octeon_i2c {scalar_t__ twsi_base; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ SW_TWSI (struct octeon_i2c*) ; 
 int SW_TWSI_R ; 
 int SW_TWSI_V ; 
 int __raw_readq (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writeq (int,scalar_t__) ; 

__attribute__((used)) static inline int octeon_i2c_reg_read(struct octeon_i2c *i2c, u64 eop_reg,
				      int *error)
{
	int tries = 1000;
	u64 tmp;

	__raw_writeq(SW_TWSI_V | eop_reg | SW_TWSI_R, i2c->twsi_base + SW_TWSI(i2c));
	do {
		tmp = __raw_readq(i2c->twsi_base + SW_TWSI(i2c));
		if (--tries < 0) {
			/* signal that the returned data is invalid */
			if (error)
				*error = -EIO;
			return 0;
		}
	} while ((tmp & SW_TWSI_V) != 0);

	return tmp & 0xFF;
}