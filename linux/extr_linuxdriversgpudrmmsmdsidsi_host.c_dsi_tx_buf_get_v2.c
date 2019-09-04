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
struct msm_dsi_host {void* tx_buf; } ;

/* Variables and functions */

void *dsi_tx_buf_get_v2(struct msm_dsi_host *msm_host)
{
	return msm_host->tx_buf;
}