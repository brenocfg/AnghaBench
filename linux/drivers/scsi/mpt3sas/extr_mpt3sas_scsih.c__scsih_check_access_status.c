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
#define  MPI2_SAS_DEVICE0_ASTATUS_DEVICE_BLOCKED 146 
#define  MPI2_SAS_DEVICE0_ASTATUS_NO_ERRORS 145 
#define  MPI2_SAS_DEVICE0_ASTATUS_ROUTE_NOT_ADDRESSABLE 144 
#define  MPI2_SAS_DEVICE0_ASTATUS_SATA_AFFILIATION_CONFLICT 143 
#define  MPI2_SAS_DEVICE0_ASTATUS_SATA_CAPABILITY_FAILED 142 
#define  MPI2_SAS_DEVICE0_ASTATUS_SATA_INIT_FAILED 141 
#define  MPI2_SAS_DEVICE0_ASTATUS_SATA_NEEDS_INITIALIZATION 140 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_AFFILIATION_CONFLICT 139 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_CHECK_POWER 138 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_DIAG 137 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_IDENTIFICATION 136 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_MAX 135 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_MDMA_SN 134 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_NOT_ADDRESSABLE 133 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_PIO_SN 132 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_UDMA_SN 131 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_UNKNOWN 130 
#define  MPI2_SAS_DEVICE0_ASTATUS_SIF_ZONING_VIOLATION 129 
#define  MPI2_SAS_DEVICE0_ASTATUS_SMP_ERROR_NOT_ADDRESSABLE 128 
 int /*<<< orphan*/  ioc_err (struct MPT3SAS_ADAPTER*,char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
_scsih_check_access_status(struct MPT3SAS_ADAPTER *ioc, u64 sas_address,
	u16 handle, u8 access_status)
{
	u8 rc = 1;
	char *desc = NULL;

	switch (access_status) {
	case MPI2_SAS_DEVICE0_ASTATUS_NO_ERRORS:
	case MPI2_SAS_DEVICE0_ASTATUS_SATA_NEEDS_INITIALIZATION:
		rc = 0;
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_SATA_CAPABILITY_FAILED:
		desc = "sata capability failed";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_SATA_AFFILIATION_CONFLICT:
		desc = "sata affiliation conflict";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_ROUTE_NOT_ADDRESSABLE:
		desc = "route not addressable";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_SMP_ERROR_NOT_ADDRESSABLE:
		desc = "smp error not addressable";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_DEVICE_BLOCKED:
		desc = "device blocked";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_SATA_INIT_FAILED:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_UNKNOWN:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_AFFILIATION_CONFLICT:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_DIAG:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_IDENTIFICATION:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_CHECK_POWER:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_PIO_SN:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_MDMA_SN:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_UDMA_SN:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_ZONING_VIOLATION:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_NOT_ADDRESSABLE:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_MAX:
		desc = "sata initialization failed";
		break;
	default:
		desc = "unknown";
		break;
	}

	if (!rc)
		return 0;

	ioc_err(ioc, "discovery errors(%s): sas_address(0x%016llx), handle(0x%04x)\n",
		desc, (u64)sas_address, handle);
	return rc;
}