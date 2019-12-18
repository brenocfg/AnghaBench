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
struct xlgmac_pdata {scalar_t__ rx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  xlgmac_disable_rx_flow_control (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_enable_rx_flow_control (struct xlgmac_pdata*) ; 

__attribute__((used)) static int xlgmac_config_rx_flow_control(struct xlgmac_pdata *pdata)
{
	if (pdata->rx_pause)
		xlgmac_enable_rx_flow_control(pdata);
	else
		xlgmac_disable_rx_flow_control(pdata);

	return 0;
}