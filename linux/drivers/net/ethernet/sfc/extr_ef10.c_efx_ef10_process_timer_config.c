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
struct efx_nic {unsigned int timer_quantum_ns; unsigned int timer_max_ns; int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 scalar_t__ EFX_EF10_WORKAROUND_35388 (struct efx_nic*) ; 
 scalar_t__ EFX_EF10_WORKAROUND_61265 (struct efx_nic*) ; 
 int /*<<< orphan*/  GET_EVQ_TMR_PROPERTIES_OUT_BUG35388_TMR_MAX_COUNT ; 
 int /*<<< orphan*/  GET_EVQ_TMR_PROPERTIES_OUT_BUG35388_TMR_NS_PER_COUNT ; 
 int /*<<< orphan*/  GET_EVQ_TMR_PROPERTIES_OUT_MCDI_TMR_MAX_NS ; 
 int /*<<< orphan*/  GET_EVQ_TMR_PROPERTIES_OUT_MCDI_TMR_STEP_NS ; 
 int /*<<< orphan*/  GET_EVQ_TMR_PROPERTIES_OUT_TMR_REG_MAX_COUNT ; 
 int /*<<< orphan*/  GET_EVQ_TMR_PROPERTIES_OUT_TMR_REG_NS_PER_COUNT ; 
 void* MCDI_DWORD (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static void efx_ef10_process_timer_config(struct efx_nic *efx,
					  const efx_dword_t *data)
{
	unsigned int max_count;

	if (EFX_EF10_WORKAROUND_61265(efx)) {
		efx->timer_quantum_ns = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_MCDI_TMR_STEP_NS);
		efx->timer_max_ns = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_MCDI_TMR_MAX_NS);
	} else if (EFX_EF10_WORKAROUND_35388(efx)) {
		efx->timer_quantum_ns = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_BUG35388_TMR_NS_PER_COUNT);
		max_count = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_BUG35388_TMR_MAX_COUNT);
		efx->timer_max_ns = max_count * efx->timer_quantum_ns;
	} else {
		efx->timer_quantum_ns = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_TMR_REG_NS_PER_COUNT);
		max_count = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_TMR_REG_MAX_COUNT);
		efx->timer_max_ns = max_count * efx->timer_quantum_ns;
	}

	netif_dbg(efx, probe, efx->net_dev,
		  "got timer properties from MC: quantum %u ns; max %u ns\n",
		  efx->timer_quantum_ns, efx->timer_max_ns);
}