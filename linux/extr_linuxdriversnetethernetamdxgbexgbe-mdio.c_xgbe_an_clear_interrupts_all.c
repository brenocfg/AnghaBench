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
 int /*<<< orphan*/  xgbe_an37_clear_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an73_clear_interrupts (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_an_clear_interrupts_all(struct xgbe_prv_data *pdata)
{
	xgbe_an73_clear_interrupts(pdata);
	xgbe_an37_clear_interrupts(pdata);
}