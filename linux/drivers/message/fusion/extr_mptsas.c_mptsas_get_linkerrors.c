#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  phy_identifier; } ;
struct sas_phy {void* phy_reset_problem_count; void* loss_of_dword_sync_count; void* running_disparity_error_count; void* invalid_dword_count; TYPE_2__ identify; } ;
typedef  int dma_addr_t ;
struct TYPE_14__ {TYPE_5__* ehdr; } ;
struct TYPE_19__ {int physAddr; int /*<<< orphan*/  action; int /*<<< orphan*/  timeout; scalar_t__ dir; int /*<<< orphan*/  pageAddr; TYPE_1__ cfghdr; } ;
struct TYPE_18__ {int ExtPageLength; int PageNumber; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageType; scalar_t__ Reserved2; scalar_t__ Reserved1; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_17__ {int /*<<< orphan*/  pcidev; } ;
struct TYPE_16__ {int /*<<< orphan*/  PhyResetProblemCount; int /*<<< orphan*/  LossDwordSynchCount; int /*<<< orphan*/  RunningDisparityErrorCount; int /*<<< orphan*/  InvalidDwordCount; } ;
typedef  TYPE_3__ SasPhyPage1_t ;
typedef  TYPE_4__ MPT_ADAPTER ;
typedef  TYPE_5__ ConfigExtendedPageHeader_t ;
typedef  TYPE_6__ CONFIGPARMS ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_EXTPAGETYPE_SAS_PHY ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  MPI_SASPHY1_PAGEVERSION ; 
 int /*<<< orphan*/  SAS_CONFIG_PAGE_TIMEOUT ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mpt_config (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mptsas_print_phy_pg1 (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_3__*,int) ; 
 TYPE_4__* phy_to_ioc (struct sas_phy*) ; 
 int /*<<< orphan*/  scsi_is_sas_phy_local (struct sas_phy*) ; 

__attribute__((used)) static int mptsas_get_linkerrors(struct sas_phy *phy)
{
	MPT_ADAPTER *ioc = phy_to_ioc(phy);
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasPhyPage1_t *buffer;
	dma_addr_t dma_handle;
	int error;

	/* FIXME: only have link errors on local phys */
	if (!scsi_is_sas_phy_local(phy))
		return -EINVAL;

	hdr.PageVersion = MPI_SASPHY1_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 1 /* page number 1*/;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_PHY;

	cfg.cfghdr.ehdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = phy->identify.phy_identifier;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;    /* read */
	cfg.timeout = SAS_CONFIG_PAGE_TIMEOUT;

	error = mpt_config(ioc, &cfg);
	if (error)
		return error;
	if (!hdr.ExtPageLength)
		return -ENXIO;

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
				      &dma_handle);
	if (!buffer)
		return -ENOMEM;

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	if (error)
		goto out_free_consistent;

	mptsas_print_phy_pg1(ioc, buffer);

	phy->invalid_dword_count = le32_to_cpu(buffer->InvalidDwordCount);
	phy->running_disparity_error_count =
		le32_to_cpu(buffer->RunningDisparityErrorCount);
	phy->loss_of_dword_sync_count =
		le32_to_cpu(buffer->LossDwordSynchCount);
	phy->phy_reset_problem_count =
		le32_to_cpu(buffer->PhyResetProblemCount);

 out_free_consistent:
	pci_free_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
	return error;
}