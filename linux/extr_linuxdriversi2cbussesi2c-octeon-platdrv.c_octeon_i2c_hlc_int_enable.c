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
struct octeon_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWSI_INT_ST_EN ; 
 int /*<<< orphan*/  octeon_i2c_write_int (struct octeon_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_i2c_hlc_int_enable(struct octeon_i2c *i2c)
{
	octeon_i2c_write_int(i2c, TWSI_INT_ST_EN);
}