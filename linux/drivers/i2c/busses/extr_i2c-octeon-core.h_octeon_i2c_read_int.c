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
typedef  int /*<<< orphan*/  u64 ;
struct octeon_i2c {scalar_t__ twsi_base; } ;

/* Variables and functions */
 scalar_t__ TWSI_INT (struct octeon_i2c*) ; 
 int /*<<< orphan*/  __raw_readq (scalar_t__) ; 

__attribute__((used)) static inline u64 octeon_i2c_read_int(struct octeon_i2c *i2c)
{
	return __raw_readq(i2c->twsi_base + TWSI_INT(i2c));
}