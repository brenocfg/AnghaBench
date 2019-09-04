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
struct nvkm_subdev {int dummy; } ;
struct nvkm_pci {int irq; int /*<<< orphan*/  pdev; scalar_t__ msi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct nvkm_pci*) ; 
 int /*<<< orphan*/  nvkm_agp_dtor (struct nvkm_pci*) ; 
 void* nvkm_pci (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
nvkm_pci_dtor(struct nvkm_subdev *subdev)
{
	struct nvkm_pci *pci = nvkm_pci(subdev);

	nvkm_agp_dtor(pci);

	if (pci->irq >= 0) {
		/* freq_irq() will call the handler, we use pci->irq == -1
		 * to signal that it's been torn down and should be a noop.
		 */
		int irq = pci->irq;
		pci->irq = -1;
		free_irq(irq, pci);
	}

	if (pci->msi)
		pci_disable_msi(pci->pdev);

	return nvkm_pci(subdev);
}