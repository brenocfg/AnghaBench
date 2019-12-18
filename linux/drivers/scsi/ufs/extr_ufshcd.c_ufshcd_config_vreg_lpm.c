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
struct ufs_vreg {int dummy; } ;
struct ufs_hba {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFS_VREG_LPM_LOAD_UA ; 
 int ufshcd_config_vreg_load (int /*<<< orphan*/ ,struct ufs_vreg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ufshcd_config_vreg_lpm(struct ufs_hba *hba,
					 struct ufs_vreg *vreg)
{
	return ufshcd_config_vreg_load(hba->dev, vreg, UFS_VREG_LPM_LOAD_UA);
}