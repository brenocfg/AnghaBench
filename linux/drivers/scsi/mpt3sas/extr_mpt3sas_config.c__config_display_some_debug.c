#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct MPT3SAS_ADAPTER {int logging_level; } ;
struct TYPE_8__ {scalar_t__ IOCLogInfo; scalar_t__ IOCStatus; } ;
struct TYPE_6__ {int PageType; int /*<<< orphan*/  PageNumber; } ;
struct TYPE_7__ {scalar_t__ PageAddress; int /*<<< orphan*/  Action; TYPE_1__ Header; int /*<<< orphan*/  ExtPageType; } ;
typedef  TYPE_2__ Mpi2ConfigRequest_t ;
typedef  TYPE_3__ MPI2DefaultReply_t ;

/* Variables and functions */
#define  MPI2_CONFIG_EXTPAGETYPE_DRIVER_MAPPING 148 
#define  MPI2_CONFIG_EXTPAGETYPE_ENCLOSURE 147 
#define  MPI2_CONFIG_EXTPAGETYPE_EXT_MANUFACTURING 146 
#define  MPI2_CONFIG_EXTPAGETYPE_LOG 145 
#define  MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE 144 
#define  MPI2_CONFIG_EXTPAGETYPE_PCIE_IO_UNIT 143 
#define  MPI2_CONFIG_EXTPAGETYPE_PCIE_LINK 142 
#define  MPI2_CONFIG_EXTPAGETYPE_PCIE_SWITCH 141 
#define  MPI2_CONFIG_EXTPAGETYPE_RAID_CONFIG 140 
#define  MPI2_CONFIG_EXTPAGETYPE_SAS_DEVICE 139 
#define  MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDER 138 
#define  MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT 137 
#define  MPI2_CONFIG_EXTPAGETYPE_SAS_PHY 136 
#define  MPI2_CONFIG_EXTPAGETYPE_SAS_PORT 135 
#define  MPI2_CONFIG_PAGETYPE_BIOS 134 
#define  MPI2_CONFIG_PAGETYPE_EXTENDED 133 
#define  MPI2_CONFIG_PAGETYPE_IOC 132 
#define  MPI2_CONFIG_PAGETYPE_IO_UNIT 131 
#define  MPI2_CONFIG_PAGETYPE_MANUFACTURING 130 
 int MPI2_CONFIG_PAGETYPE_MASK ; 
#define  MPI2_CONFIG_PAGETYPE_RAID_PHYSDISK 129 
#define  MPI2_CONFIG_PAGETYPE_RAID_VOLUME 128 
 int MPT_DEBUG_CONFIG ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 TYPE_2__* mpt3sas_base_get_msg_frame (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_config_display_some_debug(struct MPT3SAS_ADAPTER *ioc, u16 smid,
	char *calling_function_name, MPI2DefaultReply_t *mpi_reply)
{
	Mpi2ConfigRequest_t *mpi_request;
	char *desc = NULL;

	if (!(ioc->logging_level & MPT_DEBUG_CONFIG))
		return;

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	switch (mpi_request->Header.PageType & MPI2_CONFIG_PAGETYPE_MASK) {
	case MPI2_CONFIG_PAGETYPE_IO_UNIT:
		desc = "io_unit";
		break;
	case MPI2_CONFIG_PAGETYPE_IOC:
		desc = "ioc";
		break;
	case MPI2_CONFIG_PAGETYPE_BIOS:
		desc = "bios";
		break;
	case MPI2_CONFIG_PAGETYPE_RAID_VOLUME:
		desc = "raid_volume";
		break;
	case MPI2_CONFIG_PAGETYPE_MANUFACTURING:
		desc = "manufacturing";
		break;
	case MPI2_CONFIG_PAGETYPE_RAID_PHYSDISK:
		desc = "physdisk";
		break;
	case MPI2_CONFIG_PAGETYPE_EXTENDED:
		switch (mpi_request->ExtPageType) {
		case MPI2_CONFIG_EXTPAGETYPE_SAS_IO_UNIT:
			desc = "sas_io_unit";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDER:
			desc = "sas_expander";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_SAS_DEVICE:
			desc = "sas_device";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_SAS_PHY:
			desc = "sas_phy";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_LOG:
			desc = "log";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_ENCLOSURE:
			desc = "enclosure";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_RAID_CONFIG:
			desc = "raid_config";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_DRIVER_MAPPING:
			desc = "driver_mapping";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_SAS_PORT:
			desc = "sas_port";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_EXT_MANUFACTURING:
			desc = "ext_manufacturing";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_PCIE_IO_UNIT:
			desc = "pcie_io_unit";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_PCIE_SWITCH:
			desc = "pcie_switch";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_PCIE_DEVICE:
			desc = "pcie_device";
			break;
		case MPI2_CONFIG_EXTPAGETYPE_PCIE_LINK:
			desc = "pcie_link";
			break;
		}
		break;
	}

	if (!desc)
		return;

	ioc_info(ioc, "%s: %s(%d), action(%d), form(0x%08x), smid(%d)\n",
		 calling_function_name, desc,
		 mpi_request->Header.PageNumber, mpi_request->Action,
		 le32_to_cpu(mpi_request->PageAddress), smid);

	if (!mpi_reply)
		return;

	if (mpi_reply->IOCStatus || mpi_reply->IOCLogInfo)
		ioc_info(ioc, "\tiocstatus(0x%04x), loginfo(0x%08x)\n",
			 le16_to_cpu(mpi_reply->IOCStatus),
			 le32_to_cpu(mpi_reply->IOCLogInfo));
}