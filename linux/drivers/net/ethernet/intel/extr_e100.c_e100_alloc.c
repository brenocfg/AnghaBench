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
struct nic {scalar_t__ mem; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  pdev; } ;
struct mem {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int e100_alloc(struct nic *nic)
{
	nic->mem = pci_alloc_consistent(nic->pdev, sizeof(struct mem),
		&nic->dma_addr);
	return nic->mem ? 0 : -ENOMEM;
}