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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct MPT3SAS_ADAPTER {int dummy; } ;

/* Variables and functions */
#define  MPI26_PCIEDEV0_ASTATUS_CAPABILITY_FAILED 145 
#define  MPI26_PCIEDEV0_ASTATUS_DEVICE_BLOCKED 144 
#define  MPI26_PCIEDEV0_ASTATUS_INIT_FAIL_MAX 143 
#define  MPI26_PCIEDEV0_ASTATUS_MEMORY_SPACE_ACCESS_FAILED 142 
#define  MPI26_PCIEDEV0_ASTATUS_MSIX_REQUIRED 141 
#define  MPI26_PCIEDEV0_ASTATUS_NEEDS_INITIALIZATION 140 
#define  MPI26_PCIEDEV0_ASTATUS_NO_ERRORS 139 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_DEVCFG_UNSUPPORTED 138 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_EVENTCFG_FAILED 137 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_FAILURE_STATUS 136 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_GET_FEATURE_STAT_FAILED 135 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_IDENTIFY_FAILED 134 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_IDLE_TIMEOUT 133 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_QCONFIG_FAILED 132 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_QCREATION_FAILED 131 
#define  MPI26_PCIEDEV0_ASTATUS_NVME_READY_TIMEOUT 130 
#define  MPI26_PCIEDEV0_ASTATUS_UNKNOWN 129 
#define  MPI26_PCIEDEV0_ASTATUS_UNSUPPORTED_DEVICE 128 
 int /*<<< orphan*/  ioc_err (struct MPT3SAS_ADAPTER*,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
_scsih_check_pcie_access_status(struct MPT3SAS_ADAPTER *ioc, u64 wwid,
	u16 handle, u8 access_status)
{
	u8 rc = 1;
	char *desc = NULL;

	switch (access_status) {
	case MPI26_PCIEDEV0_ASTATUS_NO_ERRORS:
	case MPI26_PCIEDEV0_ASTATUS_NEEDS_INITIALIZATION:
		rc = 0;
		break;
	case MPI26_PCIEDEV0_ASTATUS_CAPABILITY_FAILED:
		desc = "PCIe device capability failed";
		break;
	case MPI26_PCIEDEV0_ASTATUS_DEVICE_BLOCKED:
		desc = "PCIe device blocked";
		ioc_info(ioc,
		    "Device with Access Status (%s): wwid(0x%016llx), "
		    "handle(0x%04x)\n ll only be added to the internal list",
		    desc, (u64)wwid, handle);
		rc = 0;
		break;
	case MPI26_PCIEDEV0_ASTATUS_MEMORY_SPACE_ACCESS_FAILED:
		desc = "PCIe device mem space access failed";
		break;
	case MPI26_PCIEDEV0_ASTATUS_UNSUPPORTED_DEVICE:
		desc = "PCIe device unsupported";
		break;
	case MPI26_PCIEDEV0_ASTATUS_MSIX_REQUIRED:
		desc = "PCIe device MSIx Required";
		break;
	case MPI26_PCIEDEV0_ASTATUS_INIT_FAIL_MAX:
		desc = "PCIe device init fail max";
		break;
	case MPI26_PCIEDEV0_ASTATUS_UNKNOWN:
		desc = "PCIe device status unknown";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_READY_TIMEOUT:
		desc = "nvme ready timeout";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_DEVCFG_UNSUPPORTED:
		desc = "nvme device configuration unsupported";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_IDENTIFY_FAILED:
		desc = "nvme identify failed";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_QCONFIG_FAILED:
		desc = "nvme qconfig failed";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_QCREATION_FAILED:
		desc = "nvme qcreation failed";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_EVENTCFG_FAILED:
		desc = "nvme eventcfg failed";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_GET_FEATURE_STAT_FAILED:
		desc = "nvme get feature stat failed";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_IDLE_TIMEOUT:
		desc = "nvme idle timeout";
		break;
	case MPI26_PCIEDEV0_ASTATUS_NVME_FAILURE_STATUS:
		desc = "nvme failure status";
		break;
	default:
		ioc_err(ioc, "NVMe discovery error(0x%02x): wwid(0x%016llx), handle(0x%04x)\n",
			access_status, (u64)wwid, handle);
		return rc;
	}

	if (!rc)
		return rc;

	ioc_info(ioc, "NVMe discovery error(%s): wwid(0x%016llx), handle(0x%04x)\n",
		 desc, (u64)wwid, handle);
	return rc;
}