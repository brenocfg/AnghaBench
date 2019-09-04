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
struct net_device {int dummy; } ;
struct TYPE_2__ {int port_id; } ;
struct bnxt {TYPE_1__ pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 int EOPNOTSUPP ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int bnxt_get_phys_port_name(struct net_device *dev, char *buf,
				   size_t len)
{
	struct bnxt *bp = netdev_priv(dev);
	int rc;

	/* The PF and it's VF-reps only support the switchdev framework */
	if (!BNXT_PF(bp))
		return -EOPNOTSUPP;

	rc = snprintf(buf, len, "p%d", bp->pf.port_id);

	if (rc >= len)
		return -EOPNOTSUPP;
	return 0;
}