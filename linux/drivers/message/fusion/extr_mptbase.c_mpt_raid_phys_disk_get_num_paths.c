#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  TYPE_2__* pRaidPhysDiskPage1_t ;
typedef  int dma_addr_t ;
struct TYPE_12__ {TYPE_4__* hdr; } ;
struct TYPE_15__ {int PageNumber; int physAddr; int PageLength; int /*<<< orphan*/  pageAddr; int /*<<< orphan*/  action; TYPE_1__ cfghdr; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_14__ {int /*<<< orphan*/  pcidev; } ;
struct TYPE_13__ {int NumPhysDiskPaths; } ;
typedef  TYPE_3__ MPT_ADAPTER ;
typedef  TYPE_4__ ConfigPageHeader_t ;
typedef  TYPE_4__ CONFIGPARMS ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_RAID_PHYSDISK ; 
 int /*<<< orphan*/  MPI_RAIDPHYSDISKPAGE1_PAGEVERSION ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpt_config (TYPE_3__*,TYPE_4__*) ; 
 TYPE_2__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_2__*,int) ; 

int
mpt_raid_phys_disk_get_num_paths(MPT_ADAPTER *ioc, u8 phys_disk_num)
{
	CONFIGPARMS		 	cfg;
	ConfigPageHeader_t	 	hdr;
	dma_addr_t			dma_handle;
	pRaidPhysDiskPage1_t		buffer = NULL;
	int				rc;

	memset(&cfg, 0 , sizeof(CONFIGPARMS));
	memset(&hdr, 0 , sizeof(ConfigPageHeader_t));

	hdr.PageVersion = MPI_RAIDPHYSDISKPAGE1_PAGEVERSION;
	hdr.PageType = MPI_CONFIG_PAGETYPE_RAID_PHYSDISK;
	hdr.PageNumber = 1;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	if (mpt_config(ioc, &cfg) != 0) {
		rc = 0;
		goto out;
	}

	if (!hdr.PageLength) {
		rc = 0;
		goto out;
	}

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4,
	    &dma_handle);

	if (!buffer) {
		rc = 0;
		goto out;
	}

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	cfg.pageAddr = phys_disk_num;

	if (mpt_config(ioc, &cfg) != 0) {
		rc = 0;
		goto out;
	}

	rc = buffer->NumPhysDiskPaths;
 out:

	if (buffer)
		pci_free_consistent(ioc->pcidev, hdr.PageLength * 4, buffer,
		    dma_handle);

	return rc;
}