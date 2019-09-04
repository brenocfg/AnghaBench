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
struct bcma_drv_pci {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool bcma_core_pci_is_in_hostmode(struct bcma_drv_pci *pc)
{
	return false;
}