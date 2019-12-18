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
struct efx_nic {int /*<<< orphan*/  rss_lock; int /*<<< orphan*/  rss_context; } ;

/* Variables and functions */
 int efx_ef10_rx_pull_rss_context_config (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_rx_pull_rss_config(struct efx_nic *efx)
{
	int rc;

	mutex_lock(&efx->rss_lock);
	rc = efx_ef10_rx_pull_rss_context_config(efx, &efx->rss_context);
	mutex_unlock(&efx->rss_lock);
	return rc;
}