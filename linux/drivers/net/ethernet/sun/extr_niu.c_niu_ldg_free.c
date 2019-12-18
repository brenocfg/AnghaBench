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
struct niu {int flags; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int NIU_FLAGS_MSIX ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_ldg_free(struct niu *np)
{
	if (np->flags & NIU_FLAGS_MSIX)
		pci_disable_msix(np->pdev);
}