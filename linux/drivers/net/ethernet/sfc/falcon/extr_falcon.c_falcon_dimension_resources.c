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
struct ef4_nic {int rx_dc_base; int tx_dc_base; } ;

/* Variables and functions */

__attribute__((used)) static int falcon_dimension_resources(struct ef4_nic *efx)
{
	efx->rx_dc_base = 0x20000;
	efx->tx_dc_base = 0x26000;
	return 0;
}