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
struct pci_sys_data {struct mvebu_pcie* private_data; } ;
struct mvebu_pcie {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mvebu_pcie *sys_to_pcie(struct pci_sys_data *sys)
{
	return sys->private_data;
}