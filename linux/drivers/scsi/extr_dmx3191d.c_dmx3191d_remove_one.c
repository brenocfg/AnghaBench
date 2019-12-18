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
struct NCR5380_hostdata {unsigned long base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX3191D_REGION_LEN ; 
 int /*<<< orphan*/  NCR5380_exit (struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct NCR5380_hostdata* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void dmx3191d_remove_one(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct NCR5380_hostdata *hostdata = shost_priv(shost);
	unsigned long io = hostdata->base;

	scsi_remove_host(shost);

	NCR5380_exit(shost);
	scsi_host_put(shost);
	release_region(io, DMX3191D_REGION_LEN);
	pci_disable_device(pdev);
}