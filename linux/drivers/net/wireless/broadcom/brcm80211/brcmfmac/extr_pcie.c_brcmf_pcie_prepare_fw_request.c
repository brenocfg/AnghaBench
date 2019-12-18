#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct brcmf_pciedev_info {TYPE_4__* pdev; TYPE_3__* settings; TYPE_1__* ci; int /*<<< orphan*/  nvram_name; int /*<<< orphan*/  fw_name; } ;
struct brcmf_fw_request {int /*<<< orphan*/  bus_nr; scalar_t__ domain_nr; int /*<<< orphan*/  board_type; TYPE_2__* items; } ;
struct brcmf_fw_name {char* member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_10__ {int /*<<< orphan*/  number; } ;
struct TYPE_9__ {TYPE_5__* bus; } ;
struct TYPE_8__ {int /*<<< orphan*/  board_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct brcmf_fw_name*) ; 
 int /*<<< orphan*/  BRCMF_FW_REQF_OPTIONAL ; 
 int /*<<< orphan*/  BRCMF_FW_TYPE_BINARY ; 
 int /*<<< orphan*/  BRCMF_FW_TYPE_NVRAM ; 
 size_t BRCMF_PCIE_FW_CODE ; 
 size_t BRCMF_PCIE_FW_NVRAM ; 
 struct brcmf_fw_request* brcmf_fw_alloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmf_fw_name*,int /*<<< orphan*/ ,struct brcmf_fw_name*,int /*<<< orphan*/ ) ; 
 struct brcmf_fw_name* brcmf_pcie_fwnames ; 
 scalar_t__ pci_domain_nr (TYPE_5__*) ; 

__attribute__((used)) static struct brcmf_fw_request *
brcmf_pcie_prepare_fw_request(struct brcmf_pciedev_info *devinfo)
{
	struct brcmf_fw_request *fwreq;
	struct brcmf_fw_name fwnames[] = {
		{ ".bin", devinfo->fw_name },
		{ ".txt", devinfo->nvram_name },
	};

	fwreq = brcmf_fw_alloc_request(devinfo->ci->chip, devinfo->ci->chiprev,
				       brcmf_pcie_fwnames,
				       ARRAY_SIZE(brcmf_pcie_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	if (!fwreq)
		return NULL;

	fwreq->items[BRCMF_PCIE_FW_CODE].type = BRCMF_FW_TYPE_BINARY;
	fwreq->items[BRCMF_PCIE_FW_NVRAM].type = BRCMF_FW_TYPE_NVRAM;
	fwreq->items[BRCMF_PCIE_FW_NVRAM].flags = BRCMF_FW_REQF_OPTIONAL;
	fwreq->board_type = devinfo->settings->board_type;
	/* NVRAM reserves PCI domain 0 for Broadcom's SDK faked bus */
	fwreq->domain_nr = pci_domain_nr(devinfo->pdev->bus) + 1;
	fwreq->bus_nr = devinfo->pdev->bus->number;

	return fwreq;
}