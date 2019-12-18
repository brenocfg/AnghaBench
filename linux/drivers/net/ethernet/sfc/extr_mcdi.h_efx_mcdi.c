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
struct efx_nic {TYPE_1__* mcdi; } ;
struct efx_mcdi_iface {int dummy; } ;
struct TYPE_2__ {struct efx_mcdi_iface iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_WARN_ON_PARANOID (int) ; 

__attribute__((used)) static inline struct efx_mcdi_iface *efx_mcdi(struct efx_nic *efx)
{
	EFX_WARN_ON_PARANOID(!efx->mcdi);
	return &efx->mcdi->iface;
}