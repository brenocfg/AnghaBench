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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ context_id; } ;
struct efx_nic {TYPE_1__ rss_context; } ;

/* Variables and functions */
 scalar_t__ EFX_EF10_RSS_CONTEXT_INVALID ; 
 int EOPNOTSUPP ; 
 int efx_ef10_rx_push_shared_rss_config (struct efx_nic*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_vf_rx_push_rss_config(struct efx_nic *efx, bool user,
					  const u32 *rx_indir_table
					  __attribute__ ((unused)),
					  const u8 *key
					  __attribute__ ((unused)))
{
	if (user)
		return -EOPNOTSUPP;
	if (efx->rss_context.context_id != EFX_EF10_RSS_CONTEXT_INVALID)
		return 0;
	return efx_ef10_rx_push_shared_rss_config(efx, NULL);
}