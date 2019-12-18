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
struct ufs_vreg_info {int /*<<< orphan*/  vdd_hba; } ;
struct ufs_hba {int /*<<< orphan*/  dev; struct ufs_vreg_info vreg_info; } ;

/* Variables and functions */
 int ufshcd_toggle_vreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ufshcd_setup_hba_vreg(struct ufs_hba *hba, bool on)
{
	struct ufs_vreg_info *info = &hba->vreg_info;

	return ufshcd_toggle_vreg(hba->dev, info->vdd_hba, on);
}