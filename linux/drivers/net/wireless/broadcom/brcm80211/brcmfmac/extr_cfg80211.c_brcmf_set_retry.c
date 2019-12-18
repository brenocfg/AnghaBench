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
struct net_device {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_C_SET_LRL ; 
 int /*<<< orphan*/  BRCMF_C_SET_SRL ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ brcmf_fil_cmd_int_set (struct brcmf_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct brcmf_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static s32 brcmf_set_retry(struct net_device *ndev, u32 retry, bool l)
{
	struct brcmf_if *ifp = netdev_priv(ndev);
	struct brcmf_pub *drvr = ifp->drvr;
	s32 err = 0;
	u32 cmd = (l ? BRCMF_C_SET_LRL : BRCMF_C_SET_SRL);

	err = brcmf_fil_cmd_int_set(ifp, cmd, retry);
	if (err) {
		bphy_err(drvr, "cmd (%d) , error (%d)\n", cmd, err);
		return err;
	}
	return err;
}