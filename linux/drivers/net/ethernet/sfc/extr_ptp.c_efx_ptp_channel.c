#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {TYPE_1__* ptp_data; } ;
struct efx_channel {int dummy; } ;
struct TYPE_2__ {struct efx_channel* channel; } ;

/* Variables and functions */

struct efx_channel *efx_ptp_channel(struct efx_nic *efx)
{
	return efx->ptp_data ? efx->ptp_data->channel : NULL;
}