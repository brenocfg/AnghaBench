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
struct hisi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  axi_bus_is_idle_v2_hw (struct hisi_hba*,int) ; 
 scalar_t__ tx_fifo_is_empty_v2_hw (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  wait_io_done_v2_hw (struct hisi_hba*,int) ; 

__attribute__((used)) static bool allowed_disable_phy_v2_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	if (tx_fifo_is_empty_v2_hw(hisi_hba, phy_no))
		return true;

	if (!axi_bus_is_idle_v2_hw(hisi_hba, phy_no))
		return false;

	if (!wait_io_done_v2_hw(hisi_hba, phy_no))
		return false;

	return true;
}