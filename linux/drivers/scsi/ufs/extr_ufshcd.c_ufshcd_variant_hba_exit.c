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
struct ufs_hba {int /*<<< orphan*/  vops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ufshcd_vops_exit (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_vops_setup_regulators (struct ufs_hba*,int) ; 

__attribute__((used)) static void ufshcd_variant_hba_exit(struct ufs_hba *hba)
{
	if (!hba->vops)
		return;

	ufshcd_vops_setup_regulators(hba, false);

	ufshcd_vops_exit(hba);
}