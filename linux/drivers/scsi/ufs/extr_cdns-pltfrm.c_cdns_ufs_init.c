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
struct ufs_hba {TYPE_1__* vops; } ;
struct TYPE_2__ {int (* phy_initialization ) (struct ufs_hba*) ;} ;

/* Variables and functions */
 int stub1 (struct ufs_hba*) ; 

__attribute__((used)) static int cdns_ufs_init(struct ufs_hba *hba)
{
	int status = 0;

	if (hba->vops && hba->vops->phy_initialization)
		status = hba->vops->phy_initialization(hba);

	return status;
}