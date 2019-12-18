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
struct msm_dsi_host {int /*<<< orphan*/  tx_gem_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_gem_put_vaddr (int /*<<< orphan*/ ) ; 

void dsi_tx_buf_put_6g(struct msm_dsi_host *msm_host)
{
	msm_gem_put_vaddr(msm_host->tx_gem_obj);
}