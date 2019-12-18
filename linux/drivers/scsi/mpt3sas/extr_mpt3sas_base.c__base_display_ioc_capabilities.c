#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_9__ {int Word; } ;
struct TYPE_11__ {int ProtocolFlags; int IOCCapabilities; TYPE_3__ FWVersion; } ;
struct TYPE_8__ {int /*<<< orphan*/  ChipName; } ;
struct TYPE_7__ {int /*<<< orphan*/  BiosVersion; } ;
struct MPT3SAS_ADAPTER {TYPE_6__ iounit_pg1; TYPE_5__ facts; int /*<<< orphan*/  hide_ir_msg; TYPE_4__* pdev; TYPE_2__ manu_pg0; TYPE_1__ bios_pg3; } ;
struct TYPE_10__ {int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int MPI2_IOCFACTS_CAPABILITY_BIDIRECTIONAL_TARGET ; 
 int MPI2_IOCFACTS_CAPABILITY_DIAG_TRACE_BUFFER ; 
 int MPI2_IOCFACTS_CAPABILITY_EEDP ; 
 int MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER ; 
 int MPI2_IOCFACTS_CAPABILITY_INTEGRATED_RAID ; 
 int MPI2_IOCFACTS_CAPABILITY_MULTICAST ; 
 int MPI2_IOCFACTS_CAPABILITY_SNAPSHOT_BUFFER ; 
 int MPI2_IOCFACTS_CAPABILITY_TASK_SET_FULL_HANDLING ; 
 int MPI2_IOCFACTS_CAPABILITY_TLR ; 
 int MPI2_IOCFACTS_PROTOCOL_NVME_DEVICES ; 
 int MPI2_IOCFACTS_PROTOCOL_SCSI_INITIATOR ; 
 int MPI2_IOCFACTS_PROTOCOL_SCSI_TARGET ; 
 int MPI2_IOUNITPAGE1_NATIVE_COMMAND_Q_DISABLE ; 
 int /*<<< orphan*/  _base_display_OEMs_branding (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
_base_display_ioc_capabilities(struct MPT3SAS_ADAPTER *ioc)
{
	int i = 0;
	char desc[16];
	u32 iounit_pg1_flags;
	u32 bios_version;

	bios_version = le32_to_cpu(ioc->bios_pg3.BiosVersion);
	strncpy(desc, ioc->manu_pg0.ChipName, 16);
	ioc_info(ioc, "%s: FWVersion(%02d.%02d.%02d.%02d), ChipRevision(0x%02x), BiosVersion(%02d.%02d.%02d.%02d)\n",
		 desc,
		 (ioc->facts.FWVersion.Word & 0xFF000000) >> 24,
		 (ioc->facts.FWVersion.Word & 0x00FF0000) >> 16,
		 (ioc->facts.FWVersion.Word & 0x0000FF00) >> 8,
		 ioc->facts.FWVersion.Word & 0x000000FF,
		 ioc->pdev->revision,
		 (bios_version & 0xFF000000) >> 24,
		 (bios_version & 0x00FF0000) >> 16,
		 (bios_version & 0x0000FF00) >> 8,
		 bios_version & 0x000000FF);

	_base_display_OEMs_branding(ioc);

	if (ioc->facts.ProtocolFlags & MPI2_IOCFACTS_PROTOCOL_NVME_DEVICES) {
		pr_info("%sNVMe", i ? "," : "");
		i++;
	}

	ioc_info(ioc, "Protocol=(");

	if (ioc->facts.ProtocolFlags & MPI2_IOCFACTS_PROTOCOL_SCSI_INITIATOR) {
		pr_cont("Initiator");
		i++;
	}

	if (ioc->facts.ProtocolFlags & MPI2_IOCFACTS_PROTOCOL_SCSI_TARGET) {
		pr_cont("%sTarget", i ? "," : "");
		i++;
	}

	i = 0;
	pr_cont("), Capabilities=(");

	if (!ioc->hide_ir_msg) {
		if (ioc->facts.IOCCapabilities &
		    MPI2_IOCFACTS_CAPABILITY_INTEGRATED_RAID) {
			pr_cont("Raid");
			i++;
		}
	}

	if (ioc->facts.IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_TLR) {
		pr_cont("%sTLR", i ? "," : "");
		i++;
	}

	if (ioc->facts.IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_MULTICAST) {
		pr_cont("%sMulticast", i ? "," : "");
		i++;
	}

	if (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_BIDIRECTIONAL_TARGET) {
		pr_cont("%sBIDI Target", i ? "," : "");
		i++;
	}

	if (ioc->facts.IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_EEDP) {
		pr_cont("%sEEDP", i ? "," : "");
		i++;
	}

	if (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_SNAPSHOT_BUFFER) {
		pr_cont("%sSnapshot Buffer", i ? "," : "");
		i++;
	}

	if (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_DIAG_TRACE_BUFFER) {
		pr_cont("%sDiag Trace Buffer", i ? "," : "");
		i++;
	}

	if (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER) {
		pr_cont("%sDiag Extended Buffer", i ? "," : "");
		i++;
	}

	if (ioc->facts.IOCCapabilities &
	    MPI2_IOCFACTS_CAPABILITY_TASK_SET_FULL_HANDLING) {
		pr_cont("%sTask Set Full", i ? "," : "");
		i++;
	}

	iounit_pg1_flags = le32_to_cpu(ioc->iounit_pg1.Flags);
	if (!(iounit_pg1_flags & MPI2_IOUNITPAGE1_NATIVE_COMMAND_Q_DISABLE)) {
		pr_cont("%sNCQ", i ? "," : "");
		i++;
	}

	pr_cont(")\n");
}