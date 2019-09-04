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
struct octeon_i2c {scalar_t__ twsi_base; } ;

/* Variables and functions */
 scalar_t__ SW_TWSI (struct octeon_i2c*) ; 
 int SW_TWSI_V ; 
 int __raw_readq (scalar_t__) ; 

__attribute__((used)) static bool octeon_i2c_hlc_test_valid(struct octeon_i2c *i2c)
{
	return (__raw_readq(i2c->twsi_base + SW_TWSI(i2c)) & SW_TWSI_V) == 0;
}