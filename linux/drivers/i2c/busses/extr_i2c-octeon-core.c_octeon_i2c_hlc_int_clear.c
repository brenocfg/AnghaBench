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
 int TWSI_INT_ST_INT ; 
 int TWSI_INT_TS_INT ; 
 int /*<<< orphan*/  octeon_i2c_write_int (struct octeon_i2c*,int) ; 

__attribute__((used)) static void octeon_i2c_hlc_int_clear(struct octeon_i2c *i2c)
{
	/* clear ST/TS events, listen for neither */
	octeon_i2c_write_int(i2c, TWSI_INT_ST_INT | TWSI_INT_TS_INT);
}