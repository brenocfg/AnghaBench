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
struct octeon_device {int pf_num; } ;
struct net_device {int dummy; } ;
struct lio_vf_rep_desc {int ifidx; struct octeon_device* oct; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct lio_vf_rep_desc* netdev_priv (struct net_device*) ; 
 int snprintf (char*,size_t,char*,int,int) ; 

__attribute__((used)) static int
lio_vf_rep_phys_port_name(struct net_device *dev,
			  char *buf, size_t len)
{
	struct lio_vf_rep_desc *vf_rep = netdev_priv(dev);
	struct octeon_device *oct = vf_rep->oct;
	int ret;

	ret = snprintf(buf, len, "pf%dvf%d", oct->pf_num,
		       vf_rep->ifidx - oct->pf_num * 64 - 1);
	if (ret >= len)
		return -EOPNOTSUPP;

	return 0;
}