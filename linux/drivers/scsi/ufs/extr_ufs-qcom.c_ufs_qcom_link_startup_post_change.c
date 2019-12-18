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
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int ufs_qcom_get_connected_tx_lanes (struct ufs_hba*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ufs_qcom_link_startup_post_change(struct ufs_hba *hba)
{
	u32 tx_lanes;

	return ufs_qcom_get_connected_tx_lanes(hba, &tx_lanes);
}