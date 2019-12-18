#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {scalar_t__ fw_type; scalar_t__ fw; scalar_t__ need_fw_reset; TYPE_1__ ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_CMDPEG_STATE ; 
 int EINTR ; 
 scalar_t__ NETXEN_DECODE_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  NETXEN_FW_VERSION_MAJOR ; 
 int /*<<< orphan*/  NETXEN_FW_VERSION_MINOR ; 
 int /*<<< orphan*/  NETXEN_FW_VERSION_SUB ; 
 int /*<<< orphan*/  NETXEN_MIU_MN_CONTROL ; 
 int /*<<< orphan*/  NETXEN_PEG_ALIVE_COUNTER ; 
 scalar_t__ NETXEN_VERSION_CODE (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 scalar_t__ NX_P3_CT_ROMIMAGE ; 
 scalar_t__ NX_P3_MN_ROMIMAGE ; 
 scalar_t__ NX_UNIFIED_ROMIMAGE ; 
 scalar_t__ PHAN_INITIALIZE_FAILED ; 
 int msleep_interruptible (int) ; 
 scalar_t__ nx_get_fw_version (struct netxen_adapter*) ; 

int
netxen_need_fw_reset(struct netxen_adapter *adapter)
{
	u32 count, old_count;
	u32 val, version, major, minor, build;
	int i, timeout;
	u8 fw_type;

	/* NX2031 firmware doesn't support heartbit */
	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		return 1;

	if (adapter->need_fw_reset)
		return 1;

	/* last attempt had failed */
	if (NXRD32(adapter, CRB_CMDPEG_STATE) == PHAN_INITIALIZE_FAILED)
		return 1;

	old_count = NXRD32(adapter, NETXEN_PEG_ALIVE_COUNTER);

	for (i = 0; i < 10; i++) {

		timeout = msleep_interruptible(200);
		if (timeout) {
			NXWR32(adapter, CRB_CMDPEG_STATE,
					PHAN_INITIALIZE_FAILED);
			return -EINTR;
		}

		count = NXRD32(adapter, NETXEN_PEG_ALIVE_COUNTER);
		if (count != old_count)
			break;
	}

	/* firmware is dead */
	if (count == old_count)
		return 1;

	/* check if we have got newer or different file firmware */
	if (adapter->fw) {

		val = nx_get_fw_version(adapter);

		version = NETXEN_DECODE_VERSION(val);

		major = NXRD32(adapter, NETXEN_FW_VERSION_MAJOR);
		minor = NXRD32(adapter, NETXEN_FW_VERSION_MINOR);
		build = NXRD32(adapter, NETXEN_FW_VERSION_SUB);

		if (version > NETXEN_VERSION_CODE(major, minor, build))
			return 1;

		if (version == NETXEN_VERSION_CODE(major, minor, build) &&
			adapter->fw_type != NX_UNIFIED_ROMIMAGE) {

			val = NXRD32(adapter, NETXEN_MIU_MN_CONTROL);
			fw_type = (val & 0x4) ?
				NX_P3_CT_ROMIMAGE : NX_P3_MN_ROMIMAGE;

			if (adapter->fw_type != fw_type)
				return 1;
		}
	}

	return 0;
}