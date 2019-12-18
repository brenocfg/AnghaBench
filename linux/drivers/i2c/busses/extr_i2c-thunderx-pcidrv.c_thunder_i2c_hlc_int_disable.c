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
 scalar_t__ TWSI_INT_ENA_W1C ; 
 int TWSI_INT_ST_INT ; 
 int TWSI_INT_TS_INT ; 
 int /*<<< orphan*/  octeon_i2c_writeq_flush (int,scalar_t__) ; 

__attribute__((used)) static void thunder_i2c_hlc_int_disable(struct octeon_i2c *i2c)
{
	octeon_i2c_writeq_flush(TWSI_INT_ST_INT | TWSI_INT_TS_INT,
				i2c->twsi_base + TWSI_INT_ENA_W1C);
}