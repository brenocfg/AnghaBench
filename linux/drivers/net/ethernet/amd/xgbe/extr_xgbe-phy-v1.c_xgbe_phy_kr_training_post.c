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
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  SIR0_KR_RT_1 ; 
 int /*<<< orphan*/  XSIR0_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_phy_kr_training_post(struct xgbe_prv_data *pdata)
{
		XSIR0_IOWRITE_BITS(pdata, SIR0_KR_RT_1, RESET, 0);
}