#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  (* build_zero_len_sge_mpi ) (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int PageNumber; int /*<<< orphan*/  PageVersion; int /*<<< orphan*/  PageType; } ;
struct TYPE_6__ {int /*<<< orphan*/  Action; int /*<<< orphan*/  PageAddress; int /*<<< orphan*/  PageBufferSGE; TYPE_1__ Header; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  Function; } ;
typedef  TYPE_2__ Mpi2ConfigRequest_t ;
typedef  int /*<<< orphan*/  Mpi2ConfigReply_t ;
typedef  int /*<<< orphan*/  Mpi26PCIeDevicePage2_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI26_PCIEDEVICE2_PAGEVERSION ; 
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE ; 
 int /*<<< orphan*/  MPI2_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  MPI2_FUNCTION_CONFIG ; 
 int /*<<< orphan*/  MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT ; 
 int _config_request (struct MPT3SAS_ADAPTER*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ *) ; 

int
mpt3sas_config_get_pcie_device_pg2(struct MPT3SAS_ADAPTER *ioc,
	Mpi2ConfigReply_t *mpi_reply, Mpi26PCIeDevicePage2_t *config_page,
	u32 form, u32 handle)
{
	Mpi2ConfigRequest_t mpi_request;
	int r;

	memset(&mpi_request, 0, sizeof(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE;
	mpi_request.Header.PageVersion = MPI26_PCIEDEVICE2_PAGEVERSION;
	mpi_request.Header.PageNumber = 2;
	ioc->build_zero_len_sge_mpi(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
			MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, NULL, 0);
	if (r)
		goto out;

	mpi_request.PageAddress = cpu_to_le32(form | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
			MPT3_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
			sizeof(*config_page));
out:
	return r;
}