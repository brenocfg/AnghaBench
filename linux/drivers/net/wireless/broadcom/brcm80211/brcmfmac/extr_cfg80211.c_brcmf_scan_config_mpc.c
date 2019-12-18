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
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_FEAT_QUIRK_NEED_MPC ; 
 scalar_t__ brcmf_feat_is_quirk_enabled (struct brcmf_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_set_mpc (struct brcmf_if*,int) ; 

__attribute__((used)) static void brcmf_scan_config_mpc(struct brcmf_if *ifp, int mpc)
{
	if (brcmf_feat_is_quirk_enabled(ifp, BRCMF_FEAT_QUIRK_NEED_MPC))
		brcmf_set_mpc(ifp, mpc);
}