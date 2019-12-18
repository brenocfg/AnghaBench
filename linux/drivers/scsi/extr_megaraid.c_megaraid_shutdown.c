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
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  __megaraid_shutdown (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void
megaraid_shutdown(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	adapter_t *adapter = (adapter_t *)host->hostdata;

	__megaraid_shutdown(adapter);
}