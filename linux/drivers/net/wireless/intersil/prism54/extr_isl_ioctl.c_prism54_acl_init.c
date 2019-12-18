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
struct islpci_acl {int /*<<< orphan*/  policy; scalar_t__ size; int /*<<< orphan*/  mac_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAC_POLICY_OPEN ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void
prism54_acl_init(struct islpci_acl *acl)
{
	mutex_init(&acl->lock);
	INIT_LIST_HEAD(&acl->mac_list);
	acl->size = 0;
	acl->policy = MAC_POLICY_OPEN;
}