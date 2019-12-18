#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {int dummy; } ;
struct TYPE_6__ {scalar_t__* u32; } ;
typedef  TYPE_1__ efx_qword_t ;
struct TYPE_7__ {scalar_t__* u32; } ;
typedef  TYPE_2__ efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (TYPE_2__,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ FRF_AZ_DRV_EV_DATA_LBN ; 
 int FRF_AZ_DRV_EV_DATA_WIDTH ; 
 int /*<<< orphan*/  FRF_AZ_DRV_EV_QID ; 
 int /*<<< orphan*/  FR_AZ_DRV_EV ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,TYPE_2__*,int /*<<< orphan*/ ) ; 

void efx_farch_generate_event(struct efx_nic *efx, unsigned int evq,
			      efx_qword_t *event)
{
	efx_oword_t drv_ev_reg;

	BUILD_BUG_ON(FRF_AZ_DRV_EV_DATA_LBN != 0 ||
		     FRF_AZ_DRV_EV_DATA_WIDTH != 64);
	drv_ev_reg.u32[0] = event->u32[0];
	drv_ev_reg.u32[1] = event->u32[1];
	drv_ev_reg.u32[2] = 0;
	drv_ev_reg.u32[3] = 0;
	EFX_SET_OWORD_FIELD(drv_ev_reg, FRF_AZ_DRV_EV_QID, evq);
	efx_writeo(efx, &drv_ev_reg, FR_AZ_DRV_EV);
}