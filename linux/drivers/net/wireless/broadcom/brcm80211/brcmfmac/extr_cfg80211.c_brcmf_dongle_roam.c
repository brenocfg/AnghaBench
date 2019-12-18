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
typedef  scalar_t__ u32 ;
struct brcmf_pub {TYPE_1__* settings; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  roamtrigger ;
typedef  int /*<<< orphan*/  roam_delta ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {scalar_t__ roamoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_ROAM_DELTA ; 
 int /*<<< orphan*/  BRCMF_C_SET_ROAM_TRIGGER ; 
 scalar_t__ BRCMF_DEFAULT_BCN_TIMEOUT_ROAM_OFF ; 
 scalar_t__ BRCMF_DEFAULT_BCN_TIMEOUT_ROAM_ON ; 
 int /*<<< orphan*/  BRCM_BAND_ALL ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  WL_ROAM_DELTA ; 
 int /*<<< orphan*/  WL_ROAM_TRIGGER_LEVEL ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ brcmf_fil_cmd_data_set (struct brcmf_if*,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ brcmf_fil_iovar_int_set (struct brcmf_if*,char*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 brcmf_dongle_roam(struct brcmf_if *ifp)
{
	struct brcmf_pub *drvr = ifp->drvr;
	s32 err;
	u32 bcn_timeout;
	__le32 roamtrigger[2];
	__le32 roam_delta[2];

	/* Configure beacon timeout value based upon roaming setting */
	if (ifp->drvr->settings->roamoff)
		bcn_timeout = BRCMF_DEFAULT_BCN_TIMEOUT_ROAM_OFF;
	else
		bcn_timeout = BRCMF_DEFAULT_BCN_TIMEOUT_ROAM_ON;
	err = brcmf_fil_iovar_int_set(ifp, "bcn_timeout", bcn_timeout);
	if (err) {
		bphy_err(drvr, "bcn_timeout error (%d)\n", err);
		goto roam_setup_done;
	}

	/* Enable/Disable built-in roaming to allow supplicant to take care of
	 * roaming.
	 */
	brcmf_dbg(INFO, "Internal Roaming = %s\n",
		  ifp->drvr->settings->roamoff ? "Off" : "On");
	err = brcmf_fil_iovar_int_set(ifp, "roam_off",
				      ifp->drvr->settings->roamoff);
	if (err) {
		bphy_err(drvr, "roam_off error (%d)\n", err);
		goto roam_setup_done;
	}

	roamtrigger[0] = cpu_to_le32(WL_ROAM_TRIGGER_LEVEL);
	roamtrigger[1] = cpu_to_le32(BRCM_BAND_ALL);
	err = brcmf_fil_cmd_data_set(ifp, BRCMF_C_SET_ROAM_TRIGGER,
				     (void *)roamtrigger, sizeof(roamtrigger));
	if (err) {
		bphy_err(drvr, "WLC_SET_ROAM_TRIGGER error (%d)\n", err);
		goto roam_setup_done;
	}

	roam_delta[0] = cpu_to_le32(WL_ROAM_DELTA);
	roam_delta[1] = cpu_to_le32(BRCM_BAND_ALL);
	err = brcmf_fil_cmd_data_set(ifp, BRCMF_C_SET_ROAM_DELTA,
				     (void *)roam_delta, sizeof(roam_delta));
	if (err) {
		bphy_err(drvr, "WLC_SET_ROAM_DELTA error (%d)\n", err);
		goto roam_setup_done;
	}

roam_setup_done:
	return err;
}