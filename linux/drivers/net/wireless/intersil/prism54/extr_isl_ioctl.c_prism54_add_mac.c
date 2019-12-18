#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct mac_entry {int /*<<< orphan*/  _list; int /*<<< orphan*/  addr; } ;
struct iw_request_info {int dummy; } ;
struct islpci_acl {int /*<<< orphan*/  lock; int /*<<< orphan*/  size; int /*<<< orphan*/  mac_list; } ;
struct TYPE_3__ {struct islpci_acl acl; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mac_entry*) ; 
 struct mac_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_add_mac(struct net_device *ndev, struct iw_request_info *info,
		struct sockaddr *awrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct islpci_acl *acl = &priv->acl;
	struct mac_entry *entry;
	struct sockaddr *addr = (struct sockaddr *) extra;

	if (addr->sa_family != ARPHRD_ETHER)
		return -EOPNOTSUPP;

	entry = kmalloc(sizeof (struct mac_entry), GFP_KERNEL);
	if (entry == NULL)
		return -ENOMEM;

	memcpy(entry->addr, addr->sa_data, ETH_ALEN);

	if (mutex_lock_interruptible(&acl->lock)) {
		kfree(entry);
		return -ERESTARTSYS;
	}
	list_add_tail(&entry->_list, &acl->mac_list);
	acl->size++;
	mutex_unlock(&acl->lock);

	return 0;
}