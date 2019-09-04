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
typedef  int /*<<< orphan*/  u16 ;
struct nvkm_pci {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wr32 ) (struct nvkm_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nvkm_pci_wr32(struct nvkm_pci *pci, u16 addr, u32 data)
{
	pci->func->wr32(pci, addr, data);
}