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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nb_smu_ind_mutex ; 
 int /*<<< orphan*/  pci_bus_read_config_dword (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_write_config_dword (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void amd_nb_index_read(struct pci_dev *pdev, unsigned int devfn,
			      unsigned int base, int offset, u32 *val)
{
	mutex_lock(&nb_smu_ind_mutex);
	pci_bus_write_config_dword(pdev->bus, devfn,
				   base, offset);
	pci_bus_read_config_dword(pdev->bus, devfn,
				  base + 4, val);
	mutex_unlock(&nb_smu_ind_mutex);
}