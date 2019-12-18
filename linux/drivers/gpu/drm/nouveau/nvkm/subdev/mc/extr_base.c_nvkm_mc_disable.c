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
typedef  scalar_t__ u64 ;
struct nvkm_device {int dummy; } ;
typedef  enum nvkm_devidx { ____Placeholder_nvkm_devidx } nvkm_devidx ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,scalar_t__,int) ; 
 scalar_t__ nvkm_mc_reset_mask (struct nvkm_device*,int,int) ; 

void
nvkm_mc_disable(struct nvkm_device *device, enum nvkm_devidx devidx)
{
	u64 pmc_enable = nvkm_mc_reset_mask(device, false, devidx);
	if (pmc_enable)
		nvkm_mask(device, 0x000200, pmc_enable, 0x00000000);
}