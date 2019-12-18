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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_mc {TYPE_1__* func; } ;
struct nvkm_device {struct nvkm_mc* mc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unk260 ) (struct nvkm_mc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ likely (struct nvkm_mc*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_mc*,int /*<<< orphan*/ ) ; 

void
nvkm_mc_unk260(struct nvkm_device *device, u32 data)
{
	struct nvkm_mc *mc = device->mc;
	if (likely(mc) && mc->func->unk260)
		mc->func->unk260(mc, data);
}