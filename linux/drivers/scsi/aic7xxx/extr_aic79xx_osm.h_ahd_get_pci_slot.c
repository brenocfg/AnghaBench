#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ahd_dev_softc_t ;
struct TYPE_3__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int PCI_SLOT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ahd_get_pci_slot(ahd_dev_softc_t pci)
{
	return (PCI_SLOT(pci->devfn));
}