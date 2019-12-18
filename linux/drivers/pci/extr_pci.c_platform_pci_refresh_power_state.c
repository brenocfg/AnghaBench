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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* refresh_state ) (struct pci_dev*) ;} ;

/* Variables and functions */
 TYPE_1__* pci_platform_pm ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

__attribute__((used)) static inline void platform_pci_refresh_power_state(struct pci_dev *dev)
{
	if (pci_platform_pm && pci_platform_pm->refresh_state)
		pci_platform_pm->refresh_state(dev);
}