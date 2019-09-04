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
typedef  int u8 ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_12__ {TYPE_4__* ehdr; } ;
struct TYPE_15__ {int PageNumber; int ExtPageLength; int /*<<< orphan*/  action; int /*<<< orphan*/  physAddr; TYPE_1__ cfghdr; int /*<<< orphan*/  PageVersion; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageType; int /*<<< orphan*/  timeout; } ;
struct TYPE_14__ {int device_missing_delay; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  io_missing_delay; } ;
struct TYPE_13__ {int ReportDeviceMissingDelay; int /*<<< orphan*/  IODeviceMissingDelay; } ;
typedef  TYPE_2__ SasIOUnitPage1_t ;
typedef  TYPE_3__ MPT_ADAPTER ;
typedef  TYPE_4__ ConfigExtendedPageHeader_t ;
typedef  TYPE_4__ CONFIGPARMS ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  MPI_SASIOUNITPAGE1_PAGEVERSION ; 
 int MPI_SAS_IOUNIT1_REPORT_MISSING_TIMEOUT_MASK ; 
 int MPI_SAS_IOUNIT1_REPORT_MISSING_UNIT_16 ; 
 int /*<<< orphan*/  SAS_CONFIG_PAGE_TIMEOUT ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int mpt_config (TYPE_3__*,TYPE_4__*) ; 
 TYPE_2__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mptsas_sas_io_unit_pg1(MPT_ADAPTER *ioc)
{
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasIOUnitPage1_t *buffer;
	dma_addr_t dma_handle;
	int error;
	u8 device_missing_delay;

	memset(&hdr, 0, sizeof(ConfigExtendedPageHeader_t));
	memset(&cfg, 0, sizeof(CONFIGPARMS));

	cfg.cfghdr.ehdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.timeout = SAS_CONFIG_PAGE_TIMEOUT;
	cfg.cfghdr.ehdr->PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	cfg.cfghdr.ehdr->ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	cfg.cfghdr.ehdr->PageVersion = MPI_SASIOUNITPAGE1_PAGEVERSION;
	cfg.cfghdr.ehdr->PageNumber = 1;

	error = mpt_config(ioc, &cfg);
	if (error)
		goto out;
	if (!hdr.ExtPageLength) {
		error = -ENXIO;
		goto out;
	}

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
					    &dma_handle);
	if (!buffer) {
		error = -ENOMEM;
		goto out;
	}

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	if (error)
		goto out_free_consistent;

	ioc->io_missing_delay  =
	    le16_to_cpu(buffer->IODeviceMissingDelay);
	device_missing_delay = buffer->ReportDeviceMissingDelay;
	ioc->device_missing_delay = (device_missing_delay & MPI_SAS_IOUNIT1_REPORT_MISSING_UNIT_16) ?
	    (device_missing_delay & MPI_SAS_IOUNIT1_REPORT_MISSING_TIMEOUT_MASK) * 16 :
	    device_missing_delay & MPI_SAS_IOUNIT1_REPORT_MISSING_TIMEOUT_MASK;

 out_free_consistent:
	pci_free_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	return error;
}