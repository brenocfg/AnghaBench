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
struct nvkm_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_pci_wr08 (struct nvkm_pci*,int,int) ; 

__attribute__((used)) static void
gf100_pci_msi_rearm(struct nvkm_pci *pci)
{
	nvkm_pci_wr08(pci, 0x0704, 0xff);
}