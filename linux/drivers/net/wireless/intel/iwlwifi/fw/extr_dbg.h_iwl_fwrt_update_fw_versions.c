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
struct iwl_umac_alive {int /*<<< orphan*/  umac_minor; int /*<<< orphan*/  umac_major; } ;
struct iwl_lmac_alive {int /*<<< orphan*/  ucode_minor; int /*<<< orphan*/  ucode_major; int /*<<< orphan*/  ver_subtype; int /*<<< orphan*/  ver_type; } ;
struct TYPE_3__ {void* umac_minor; void* umac_major; void* lmac_minor; void* lmac_major; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ fw_ver; } ;
struct iwl_fw_runtime {TYPE_2__ dump; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_fwrt_update_fw_versions(struct iwl_fw_runtime *fwrt,
					       struct iwl_lmac_alive *lmac,
					       struct iwl_umac_alive *umac)
{
	if (lmac) {
		fwrt->dump.fw_ver.type = lmac->ver_type;
		fwrt->dump.fw_ver.subtype = lmac->ver_subtype;
		fwrt->dump.fw_ver.lmac_major = le32_to_cpu(lmac->ucode_major);
		fwrt->dump.fw_ver.lmac_minor = le32_to_cpu(lmac->ucode_minor);
	}

	if (umac) {
		fwrt->dump.fw_ver.umac_major = le32_to_cpu(umac->umac_major);
		fwrt->dump.fw_ver.umac_minor = le32_to_cpu(umac->umac_minor);
	}
}