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
struct mvumi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvumi_flush_cache (struct mvumi_hba*) ; 
 struct mvumi_hba* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void mvumi_shutdown(struct pci_dev *pdev)
{
	struct mvumi_hba *mhba = pci_get_drvdata(pdev);

	mvumi_flush_cache(mhba);
}