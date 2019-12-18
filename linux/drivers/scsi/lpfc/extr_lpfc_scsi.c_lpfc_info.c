#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {char* ModelDesc; scalar_t__* Port; TYPE_2__* pcidev; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  lpfcinfobuf ;
struct TYPE_4__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_check_pci_resettable (struct lpfc_hba*) ; 
 int lpfc_sli_port_speed_get (struct lpfc_hba*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,...) ; 
 int strlcat (char*,char*,int) ; 

const char *
lpfc_info(struct Scsi_Host *host)
{
	struct lpfc_vport *vport = (struct lpfc_vport *) host->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	int link_speed = 0;
	static char lpfcinfobuf[384];
	char tmp[384] = {0};

	memset(lpfcinfobuf, 0, sizeof(lpfcinfobuf));
	if (phba && phba->pcidev){
		/* Model Description */
		scnprintf(tmp, sizeof(tmp), phba->ModelDesc);
		if (strlcat(lpfcinfobuf, tmp, sizeof(lpfcinfobuf)) >=
		    sizeof(lpfcinfobuf))
			goto buffer_done;

		/* PCI Info */
		scnprintf(tmp, sizeof(tmp),
			  " on PCI bus %02x device %02x irq %d",
			  phba->pcidev->bus->number, phba->pcidev->devfn,
			  phba->pcidev->irq);
		if (strlcat(lpfcinfobuf, tmp, sizeof(lpfcinfobuf)) >=
		    sizeof(lpfcinfobuf))
			goto buffer_done;

		/* Port Number */
		if (phba->Port[0]) {
			scnprintf(tmp, sizeof(tmp), " port %s", phba->Port);
			if (strlcat(lpfcinfobuf, tmp, sizeof(lpfcinfobuf)) >=
			    sizeof(lpfcinfobuf))
				goto buffer_done;
		}

		/* Link Speed */
		link_speed = lpfc_sli_port_speed_get(phba);
		if (link_speed != 0) {
			scnprintf(tmp, sizeof(tmp),
				  " Logical Link Speed: %d Mbps", link_speed);
			if (strlcat(lpfcinfobuf, tmp, sizeof(lpfcinfobuf)) >=
			    sizeof(lpfcinfobuf))
				goto buffer_done;
		}

		/* PCI resettable */
		if (!lpfc_check_pci_resettable(phba)) {
			scnprintf(tmp, sizeof(tmp), " PCI resettable");
			strlcat(lpfcinfobuf, tmp, sizeof(lpfcinfobuf));
		}
	}

buffer_done:
	return lpfcinfobuf;
}