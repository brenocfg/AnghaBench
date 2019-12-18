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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {int fw_type; TYPE_1__ ahw; } ;

/* Variables and functions */
 int NX_FLASH_ROMIMAGE ; 
 int /*<<< orphan*/  NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_IS_REVISION_P3P (int /*<<< orphan*/ ) ; 
#define  NX_P2_MN_ROMIMAGE 132 
#define  NX_P3_CT_ROMIMAGE 131 
#define  NX_P3_MN_ROMIMAGE 130 
#define  NX_UNIFIED_ROMIMAGE 129 
#define  NX_UNKNOWN_ROMIMAGE 128 
 int /*<<< orphan*/  netxen_p3_has_mn (struct netxen_adapter*) ; 

__attribute__((used)) static void
nx_get_next_fwtype(struct netxen_adapter *adapter)
{
	u8 fw_type;

	switch (adapter->fw_type) {
	case NX_UNKNOWN_ROMIMAGE:
		fw_type = NX_UNIFIED_ROMIMAGE;
		break;

	case NX_UNIFIED_ROMIMAGE:
		if (NX_IS_REVISION_P3P(adapter->ahw.revision_id))
			fw_type = NX_FLASH_ROMIMAGE;
		else if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
			fw_type = NX_P2_MN_ROMIMAGE;
		else if (netxen_p3_has_mn(adapter))
			fw_type = NX_P3_MN_ROMIMAGE;
		else
			fw_type = NX_P3_CT_ROMIMAGE;
		break;

	case NX_P3_MN_ROMIMAGE:
		fw_type = NX_P3_CT_ROMIMAGE;
		break;

	case NX_P2_MN_ROMIMAGE:
	case NX_P3_CT_ROMIMAGE:
	default:
		fw_type = NX_FLASH_ROMIMAGE;
		break;
	}

	adapter->fw_type = fw_type;
}