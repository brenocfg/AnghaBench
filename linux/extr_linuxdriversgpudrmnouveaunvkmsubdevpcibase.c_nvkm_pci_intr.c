#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct nvkm_device* device; } ;
struct nvkm_pci {scalar_t__ irq; TYPE_2__* func; scalar_t__ msi; TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* msi_rearm ) (struct nvkm_pci*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  nvkm_mc_intr (struct nvkm_device*,int*) ; 
 int /*<<< orphan*/  nvkm_mc_intr_rearm (struct nvkm_device*) ; 
 int /*<<< orphan*/  nvkm_mc_intr_unarm (struct nvkm_device*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_pci*) ; 

__attribute__((used)) static irqreturn_t
nvkm_pci_intr(int irq, void *arg)
{
	struct nvkm_pci *pci = arg;
	struct nvkm_device *device = pci->subdev.device;
	bool handled = false;

	if (pci->irq < 0)
		return IRQ_HANDLED;

	nvkm_mc_intr_unarm(device);
	if (pci->msi)
		pci->func->msi_rearm(pci);
	nvkm_mc_intr(device, &handled);
	nvkm_mc_intr_rearm(device);
	return handled ? IRQ_HANDLED : IRQ_NONE;
}