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
struct amd_ntb_dev {int peer_sta; int /*<<< orphan*/  cntl_sta; } ;

/* Variables and functions */
 int AMD_LINK_DOWN_EVENT ; 
 int AMD_LINK_UP_EVENT ; 
 int AMD_PEER_D0_EVENT ; 
 int AMD_PEER_RESET_EVENT ; 
 int NTB_LNK_STA_ACTIVE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd_link_is_up(struct amd_ntb_dev *ndev)
{
	if (!ndev->peer_sta)
		return NTB_LNK_STA_ACTIVE(ndev->cntl_sta);

	if (ndev->peer_sta & AMD_LINK_UP_EVENT) {
		ndev->peer_sta = 0;
		return 1;
	}

	/* If peer_sta is reset or D0 event, the ISR has
	 * started a timer to check link status of hardware.
	 * So here just clear status bit. And if peer_sta is
	 * D3 or PME_TO, D0/reset event will be happened when
	 * system wakeup/poweron, so do nothing here.
	 */
	if (ndev->peer_sta & AMD_PEER_RESET_EVENT)
		ndev->peer_sta &= ~AMD_PEER_RESET_EVENT;
	else if (ndev->peer_sta & (AMD_PEER_D0_EVENT | AMD_LINK_DOWN_EVENT))
		ndev->peer_sta = 0;

	return 0;
}