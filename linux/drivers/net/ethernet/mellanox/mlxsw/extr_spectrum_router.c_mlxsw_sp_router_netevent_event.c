#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct neighbour {int /*<<< orphan*/  dev; TYPE_4__* tbl; } ;
struct neigh_parms {int /*<<< orphan*/  dev; TYPE_1__* tbl; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_netevent_work {int /*<<< orphan*/  work; struct neighbour* n; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {TYPE_3__* router; } ;
struct TYPE_8__ {int /*<<< orphan*/  family; } ;
struct TYPE_6__ {unsigned long interval; } ;
struct TYPE_7__ {TYPE_2__ neighs_update; } ;
struct TYPE_5__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  DELAY_PROBE_TIME ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEIGH_VAR (struct neigh_parms*,int /*<<< orphan*/ ) ; 
#define  NETEVENT_DELAY_PROBE_TIME_UPDATE 132 
#define  NETEVENT_IPV4_FWD_UPDATE_PRIORITY_UPDATE 131 
#define  NETEVENT_IPV4_MPATH_HASH_UPDATE 130 
#define  NETEVENT_IPV6_MPATH_HASH_UPDATE 129 
#define  NETEVENT_NEIGH_UPDATE 128 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 unsigned long jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_netevent_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_port_dev_put (struct mlxsw_sp_port*) ; 
 struct mlxsw_sp_port* mlxsw_sp_port_lower_dev_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_router_mp_hash_event_work ; 
 int /*<<< orphan*/  mlxsw_sp_router_neigh_event_work ; 
 int mlxsw_sp_router_schedule_work (void*,struct notifier_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_router_update_priority_work ; 
 int /*<<< orphan*/  neigh_clone (struct neighbour*) ; 

__attribute__((used)) static int mlxsw_sp_router_netevent_event(struct notifier_block *nb,
					  unsigned long event, void *ptr)
{
	struct mlxsw_sp_netevent_work *net_work;
	struct mlxsw_sp_port *mlxsw_sp_port;
	struct mlxsw_sp *mlxsw_sp;
	unsigned long interval;
	struct neigh_parms *p;
	struct neighbour *n;

	switch (event) {
	case NETEVENT_DELAY_PROBE_TIME_UPDATE:
		p = ptr;

		/* We don't care about changes in the default table. */
		if (!p->dev || (p->tbl->family != AF_INET &&
				p->tbl->family != AF_INET6))
			return NOTIFY_DONE;

		/* We are in atomic context and can't take RTNL mutex,
		 * so use RCU variant to walk the device chain.
		 */
		mlxsw_sp_port = mlxsw_sp_port_lower_dev_hold(p->dev);
		if (!mlxsw_sp_port)
			return NOTIFY_DONE;

		mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
		interval = jiffies_to_msecs(NEIGH_VAR(p, DELAY_PROBE_TIME));
		mlxsw_sp->router->neighs_update.interval = interval;

		mlxsw_sp_port_dev_put(mlxsw_sp_port);
		break;
	case NETEVENT_NEIGH_UPDATE:
		n = ptr;

		if (n->tbl->family != AF_INET && n->tbl->family != AF_INET6)
			return NOTIFY_DONE;

		mlxsw_sp_port = mlxsw_sp_port_lower_dev_hold(n->dev);
		if (!mlxsw_sp_port)
			return NOTIFY_DONE;

		net_work = kzalloc(sizeof(*net_work), GFP_ATOMIC);
		if (!net_work) {
			mlxsw_sp_port_dev_put(mlxsw_sp_port);
			return NOTIFY_BAD;
		}

		INIT_WORK(&net_work->work, mlxsw_sp_router_neigh_event_work);
		net_work->mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
		net_work->n = n;

		/* Take a reference to ensure the neighbour won't be
		 * destructed until we drop the reference in delayed
		 * work.
		 */
		neigh_clone(n);
		mlxsw_core_schedule_work(&net_work->work);
		mlxsw_sp_port_dev_put(mlxsw_sp_port);
		break;
	case NETEVENT_IPV4_MPATH_HASH_UPDATE:
	case NETEVENT_IPV6_MPATH_HASH_UPDATE:
		return mlxsw_sp_router_schedule_work(ptr, nb,
				mlxsw_sp_router_mp_hash_event_work);

	case NETEVENT_IPV4_FWD_UPDATE_PRIORITY_UPDATE:
		return mlxsw_sp_router_schedule_work(ptr, nb,
				mlxsw_sp_router_update_priority_work);
	}

	return NOTIFY_DONE;
}