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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bypass_pci_id_table ; 
 int /*<<< orphan*/  pci_match_id (int /*<<< orphan*/ ,struct pci_dev*) ; 

__attribute__((used)) static inline bool is_bypassed_id(struct pci_dev *pdev)
{
	return !!pci_match_id(bypass_pci_id_table, pdev);
}