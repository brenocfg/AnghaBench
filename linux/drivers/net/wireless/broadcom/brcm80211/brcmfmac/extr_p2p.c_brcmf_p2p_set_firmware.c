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
typedef  int /*<<< orphan*/  u8 ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_DOWN ; 
 int /*<<< orphan*/  BRCMF_C_UP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_fil_cmd_int_set (struct brcmf_if*,int /*<<< orphan*/ ,int) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fil_iovar_int_set (struct brcmf_if*,char*,int) ; 

__attribute__((used)) static int brcmf_p2p_set_firmware(struct brcmf_if *ifp, u8 *p2p_mac)
{
	struct brcmf_pub *drvr = ifp->drvr;
	s32 ret = 0;

	brcmf_fil_cmd_int_set(ifp, BRCMF_C_DOWN, 1);
	brcmf_fil_iovar_int_set(ifp, "apsta", 1);
	brcmf_fil_cmd_int_set(ifp, BRCMF_C_UP, 1);

	/* In case of COB type, firmware has default mac address
	 * After Initializing firmware, we have to set current mac address to
	 * firmware for P2P device address. This must be done with discovery
	 * disabled.
	 */
	brcmf_fil_iovar_int_set(ifp, "p2p_disc", 0);

	ret = brcmf_fil_iovar_data_set(ifp, "p2p_da_override", p2p_mac,
				       ETH_ALEN);
	if (ret)
		bphy_err(drvr, "failed to update device address ret %d\n", ret);

	return ret;
}