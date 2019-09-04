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
struct nvkm_fault {int /*<<< orphan*/  nrpfb; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nvkm_notify_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gv100_fault_init(struct nvkm_fault *fault)
{
	nvkm_mask(fault->subdev.device, 0x100a2c, 0x80000000, 0x80000000);
	nvkm_notify_get(&fault->nrpfb);
}