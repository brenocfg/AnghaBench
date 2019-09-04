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
struct nvkm_device {int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_pci_rom_shadow (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
prom_fini(void *data)
{
	struct nvkm_device *device = data;
	nvkm_pci_rom_shadow(device->pci, true);
}