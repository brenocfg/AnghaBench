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
struct xgbe_prv_data {unsigned int channel_count; int /*<<< orphan*/ * channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_disable_rx_tx_int (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_disable_rx_tx_ints(struct xgbe_prv_data *pdata)
{
	unsigned int i;

	for (i = 0; i < pdata->channel_count; i++)
		xgbe_disable_rx_tx_int(pdata, pdata->channel[i]);
}