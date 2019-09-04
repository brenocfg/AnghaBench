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
typedef  int /*<<< orphan*/  u32 ;
struct netxen_adapter {size_t file_prd_off; scalar_t__ fw_type; struct firmware* fw; } ;
struct firmware {int /*<<< orphan*/ * data; } ;
typedef  size_t __le32 ;

/* Variables and functions */
 size_t NX_BIOS_VERSION_OFFSET ; 
 scalar_t__ NX_UNIFIED_ROMIMAGE ; 
 int NX_UNI_BIOS_VERSION_OFF ; 
 size_t cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le32
nx_get_bios_version(struct netxen_adapter *adapter)
{
	const struct firmware *fw = adapter->fw;
	__le32 bios_ver, prd_off = adapter->file_prd_off;

	if (adapter->fw_type == NX_UNIFIED_ROMIMAGE) {
		bios_ver = cpu_to_le32(*((u32 *) (&fw->data[prd_off])
						+ NX_UNI_BIOS_VERSION_OFF));
		return (bios_ver << 16) + ((bios_ver >> 8) & 0xff00) +
							(bios_ver >> 24);
	} else
		return cpu_to_le32(*(u32 *)&fw->data[NX_BIOS_VERSION_OFFSET]);

}