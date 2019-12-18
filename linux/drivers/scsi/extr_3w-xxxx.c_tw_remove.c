#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ TW_Device_Extension ;

/* Variables and functions */
 int /*<<< orphan*/  __tw_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_device_extension_count ; 
 int /*<<< orphan*/  tw_free_device_extension (TYPE_1__*) ; 
 int twe_major ; 
 int /*<<< orphan*/  unregister_chrdev (int,char*) ; 

__attribute__((used)) static void tw_remove(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	scsi_remove_host(tw_dev->host);

	/* Unregister character device */
	if (twe_major >= 0) {
		unregister_chrdev(twe_major, "twe");
		twe_major = -1;
	}

	/* Shutdown the card */
	__tw_shutdown(tw_dev);

	/* Free up the mem region */
	pci_release_regions(pdev);

	/* Free up device extension resources */
	tw_free_device_extension(tw_dev);

	scsi_host_put(tw_dev->host);
	pci_disable_device(pdev);
	tw_device_extension_count--;
}