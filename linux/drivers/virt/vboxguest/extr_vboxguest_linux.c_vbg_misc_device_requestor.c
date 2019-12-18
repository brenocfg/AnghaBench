#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_gid; } ;
struct TYPE_4__ {TYPE_1__* cred; } ;
struct TYPE_3__ {int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int VMMDEV_REQUESTOR_CON_DONT_KNOW ; 
 int VMMDEV_REQUESTOR_GRP_VBOX ; 
 int VMMDEV_REQUESTOR_TRUST_NOT_GIVEN ; 
 int VMMDEV_REQUESTOR_USERMODE ; 
 int VMMDEV_REQUESTOR_USR_ROOT ; 
 int VMMDEV_REQUESTOR_USR_USER ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  current_user_ns () ; 
 scalar_t__ from_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ in_egroup_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 vbg_misc_device_requestor(struct inode *inode)
{
	u32 requestor = VMMDEV_REQUESTOR_USERMODE |
			VMMDEV_REQUESTOR_CON_DONT_KNOW |
			VMMDEV_REQUESTOR_TRUST_NOT_GIVEN;

	if (from_kuid(current_user_ns(), current->cred->uid) == 0)
		requestor |= VMMDEV_REQUESTOR_USR_ROOT;
	else
		requestor |= VMMDEV_REQUESTOR_USR_USER;

	if (in_egroup_p(inode->i_gid))
		requestor |= VMMDEV_REQUESTOR_GRP_VBOX;

	return requestor;
}