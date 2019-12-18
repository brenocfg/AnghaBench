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
typedef  enum ufs_notify_change_status { ____Placeholder_ufs_notify_change_status } ufs_notify_change_status ;

/* Variables and functions */
 int PRE_CHANGE ; 
 int cdns_ufs_set_hclkdiv (struct ufs_hba*) ; 

__attribute__((used)) static int cdns_ufs_hce_enable_notify(struct ufs_hba *hba,
				      enum ufs_notify_change_status status)
{
	if (status != PRE_CHANGE)
		return 0;

	return cdns_ufs_set_hclkdiv(hba);
}