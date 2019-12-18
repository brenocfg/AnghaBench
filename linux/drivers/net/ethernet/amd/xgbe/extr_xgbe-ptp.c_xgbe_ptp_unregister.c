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
struct xgbe_prv_data {scalar_t__ ptp_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptp_clock_unregister (scalar_t__) ; 

void xgbe_ptp_unregister(struct xgbe_prv_data *pdata)
{
	if (pdata->ptp_clock)
		ptp_clock_unregister(pdata->ptp_clock);
}