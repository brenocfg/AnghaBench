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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSP32_DEBUG_REGISTER ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp32_release (struct Scsi_Host*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void nsp32_remove(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);

	nsp32_dbg(NSP32_DEBUG_REGISTER, "enter");

        scsi_remove_host(host);

	nsp32_release(host);

	scsi_host_put(host);
}