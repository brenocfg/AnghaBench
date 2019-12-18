#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct netxen_adapter {scalar_t__ fw_type; TYPE_1__* fw; } ;
struct TYPE_4__ {int /*<<< orphan*/  findex; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t NETXEN_IMAGE_START ; 
 scalar_t__ NX_UNIFIED_ROMIMAGE ; 
 int /*<<< orphan*/  NX_UNI_DIR_SECT_FW ; 
 int /*<<< orphan*/  NX_UNI_FIRMWARE_IDX_OFF ; 
 size_t cpu_to_le32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* nx_get_data_desc (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 *
nx_get_fw_offs(struct netxen_adapter *adapter)
{
	u32 offs = NETXEN_IMAGE_START;

	if (adapter->fw_type == NX_UNIFIED_ROMIMAGE)
		offs = cpu_to_le32((nx_get_data_desc(adapter,
					NX_UNI_DIR_SECT_FW,
					NX_UNI_FIRMWARE_IDX_OFF))->findex);

	return (u8 *)&adapter->fw->data[offs];
}