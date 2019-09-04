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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IC_INTR_MASK ; 
 int /*<<< orphan*/  XGBE_DEFAULT_INT_MASK ; 
 int /*<<< orphan*/  XI2C_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_i2c_enable_interrupts(struct xgbe_prv_data *pdata)
{
	XI2C_IOWRITE(pdata, IC_INTR_MASK, XGBE_DEFAULT_INT_MASK);
}