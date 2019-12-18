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
struct mlxsw_sp_ipip_ops {int ul_proto; } ;
struct mlxsw_sp_ipip_entry {int ipipt; int /*<<< orphan*/  parms4; struct net_device* ol_dev; int /*<<< orphan*/  ol_lb; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;
struct TYPE_2__ {struct mlxsw_sp_ipip_ops** ipip_ops_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlxsw_sp_ipip_entry* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_ipip_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_ipip_entry*) ; 
 struct mlxsw_sp_ipip_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_netdev_parms4 (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_ol_ipip_lb_create (struct mlxsw_sp*,int,struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_sp_ipip_entry *
mlxsw_sp_ipip_entry_alloc(struct mlxsw_sp *mlxsw_sp,
			  enum mlxsw_sp_ipip_type ipipt,
			  struct net_device *ol_dev)
{
	const struct mlxsw_sp_ipip_ops *ipip_ops;
	struct mlxsw_sp_ipip_entry *ipip_entry;
	struct mlxsw_sp_ipip_entry *ret = NULL;

	ipip_ops = mlxsw_sp->router->ipip_ops_arr[ipipt];
	ipip_entry = kzalloc(sizeof(*ipip_entry), GFP_KERNEL);
	if (!ipip_entry)
		return ERR_PTR(-ENOMEM);

	ipip_entry->ol_lb = mlxsw_sp_ipip_ol_ipip_lb_create(mlxsw_sp, ipipt,
							    ol_dev, NULL);
	if (IS_ERR(ipip_entry->ol_lb)) {
		ret = ERR_CAST(ipip_entry->ol_lb);
		goto err_ol_ipip_lb_create;
	}

	ipip_entry->ipipt = ipipt;
	ipip_entry->ol_dev = ol_dev;

	switch (ipip_ops->ul_proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		ipip_entry->parms4 = mlxsw_sp_ipip_netdev_parms4(ol_dev);
		break;
	case MLXSW_SP_L3_PROTO_IPV6:
		WARN_ON(1);
		break;
	}

	return ipip_entry;

err_ol_ipip_lb_create:
	kfree(ipip_entry);
	return ret;
}