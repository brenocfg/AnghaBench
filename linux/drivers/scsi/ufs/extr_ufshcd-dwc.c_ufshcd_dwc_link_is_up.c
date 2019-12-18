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
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int UFSHCD_LINK_IS_UP ; 
 int /*<<< orphan*/  UIC_ARG_MIB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VS_POWERSTATE ; 
 int /*<<< orphan*/  ufshcd_dme_get (struct ufs_hba*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ufshcd_set_link_active (struct ufs_hba*) ; 

__attribute__((used)) static int ufshcd_dwc_link_is_up(struct ufs_hba *hba)
{
	int dme_result = 0;

	ufshcd_dme_get(hba, UIC_ARG_MIB(VS_POWERSTATE), &dme_result);

	if (dme_result == UFSHCD_LINK_IS_UP) {
		ufshcd_set_link_active(hba);
		return 0;
	}

	return 1;
}