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
typedef  int /*<<< orphan*/  u32 ;
struct ef4_nic {int dummy; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_AZ_ALTERA_BUILD_VER ; 
 int /*<<< orphan*/  FR_AZ_ALTERA_BUILD ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u32 ef4_farch_fpga_ver(struct ef4_nic *efx)
{
	ef4_oword_t altera_build;
	ef4_reado(efx, &altera_build, FR_AZ_ALTERA_BUILD);
	return EF4_OWORD_FIELD(altera_build, FRF_AZ_ALTERA_BUILD_VER);
}