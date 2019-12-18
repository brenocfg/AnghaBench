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
struct TYPE_4__ {char* firmware_path; } ;
struct TYPE_3__ {scalar_t__ fw_alternative_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_FW_ALTPATH_LEN ; 
 scalar_t__ brcmf_firmware_path ; 
 TYPE_2__ brcmf_mp_global ; 
 TYPE_1__* brcmfmac_pdata ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_mp_attach(void)
{
	/* If module param firmware path is set then this will always be used,
	 * if not set then if available use the platform data version. To make
	 * sure it gets initialized at all, always copy the module param version
	 */
	strlcpy(brcmf_mp_global.firmware_path, brcmf_firmware_path,
		BRCMF_FW_ALTPATH_LEN);
	if ((brcmfmac_pdata) && (brcmfmac_pdata->fw_alternative_path) &&
	    (brcmf_mp_global.firmware_path[0] == '\0')) {
		strlcpy(brcmf_mp_global.firmware_path,
			brcmfmac_pdata->fw_alternative_path,
			BRCMF_FW_ALTPATH_LEN);
	}
}