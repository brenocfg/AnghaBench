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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nvkm_fault {TYPE_1__ subdev; int /*<<< orphan*/  nrpfb; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nvkm_notify_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gv100_fault_fini(struct nvkm_fault *fault)
{
	nvkm_notify_put(&fault->nrpfb);
	nvkm_mask(fault->subdev.device, 0x100a34, 0x80000000, 0x80000000);
}