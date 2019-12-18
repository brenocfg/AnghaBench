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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_qdisc {int type; } ;
struct nfp_abm_link {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum nfp_qdisc_type { ____Placeholder_nfp_qdisc_type } nfp_qdisc_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 struct nfp_qdisc* nfp_abm_qdisc_alloc (struct net_device*,struct nfp_abm_link*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct nfp_qdisc* nfp_abm_qdisc_find (struct nfp_abm_link*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_abm_qdisc_replace(struct net_device *netdev, struct nfp_abm_link *alink,
		      enum nfp_qdisc_type type, u32 parent_handle, u32 handle,
		      unsigned int children, struct nfp_qdisc **qdisc)
{
	*qdisc = nfp_abm_qdisc_find(alink, handle);
	if (*qdisc) {
		if (WARN_ON((*qdisc)->type != type))
			return -EINVAL;
		return 1;
	}

	*qdisc = nfp_abm_qdisc_alloc(netdev, alink, type, parent_handle, handle,
				     children);
	return *qdisc ? 0 : -ENOMEM;
}