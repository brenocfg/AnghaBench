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
struct TYPE_2__ {scalar_t__ topo; } ;
struct intel_ntb_dev {int /*<<< orphan*/  lnk_sta; TYPE_1__ ntb; } ;

/* Variables and functions */
 int NTB_LNK_STA_ACTIVE (int /*<<< orphan*/ ) ; 
 scalar_t__ NTB_TOPO_SEC ; 

int xeon_link_is_up(struct intel_ntb_dev *ndev)
{
	if (ndev->ntb.topo == NTB_TOPO_SEC)
		return 1;

	return NTB_LNK_STA_ACTIVE(ndev->lnk_sta);
}