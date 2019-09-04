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
 int /*<<< orphan*/  IC_CLR_INTR ; 
 int /*<<< orphan*/  XI2C_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_i2c_clear_all_interrupts(struct xgbe_prv_data *pdata)
{
	XI2C_IOREAD(pdata, IC_CLR_INTR);
}