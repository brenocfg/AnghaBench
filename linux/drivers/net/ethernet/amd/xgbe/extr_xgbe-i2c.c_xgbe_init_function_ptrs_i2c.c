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
struct xgbe_i2c_if {int /*<<< orphan*/  i2c_isr; int /*<<< orphan*/  i2c_xfer; int /*<<< orphan*/  i2c_stop; int /*<<< orphan*/  i2c_start; int /*<<< orphan*/  i2c_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_i2c_combined_isr ; 
 int /*<<< orphan*/  xgbe_i2c_init ; 
 int /*<<< orphan*/  xgbe_i2c_start ; 
 int /*<<< orphan*/  xgbe_i2c_stop ; 
 int /*<<< orphan*/  xgbe_i2c_xfer ; 

void xgbe_init_function_ptrs_i2c(struct xgbe_i2c_if *i2c_if)
{
	i2c_if->i2c_init		= xgbe_i2c_init;

	i2c_if->i2c_start		= xgbe_i2c_start;
	i2c_if->i2c_stop		= xgbe_i2c_stop;

	i2c_if->i2c_xfer		= xgbe_i2c_xfer;

	i2c_if->i2c_isr			= xgbe_i2c_combined_isr;
}