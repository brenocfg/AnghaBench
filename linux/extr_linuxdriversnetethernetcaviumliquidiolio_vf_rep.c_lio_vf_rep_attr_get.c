#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  id_len; } ;
struct TYPE_6__ {TYPE_2__ ppid; } ;
struct switchdev_attr {int id; TYPE_3__ u; } ;
struct net_device {int dummy; } ;
struct lio_vf_rep_desc {struct net_device* parent_ndev; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_addr; } ;
struct lio {TYPE_1__ linfo; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct lio* GET_LIO (struct net_device*) ; 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,void*) ; 
 struct lio_vf_rep_desc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
lio_vf_rep_attr_get(struct net_device *dev, struct switchdev_attr *attr)
{
	struct lio_vf_rep_desc *vf_rep = netdev_priv(dev);
	struct net_device *parent_ndev = vf_rep->parent_ndev;
	struct lio *lio = GET_LIO(parent_ndev);

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
		attr->u.ppid.id_len = ETH_ALEN;
		ether_addr_copy(attr->u.ppid.id,
				(void *)&lio->linfo.hw_addr + 2);
		break;

	default:
		return -EOPNOTSUPP;
	}

	return 0;
}