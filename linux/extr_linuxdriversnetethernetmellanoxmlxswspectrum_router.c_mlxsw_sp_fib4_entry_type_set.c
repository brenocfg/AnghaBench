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
union mlxsw_sp_l3addr {int /*<<< orphan*/  addr4; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_ipip_entry {TYPE_1__* ol_dev; } ;
struct mlxsw_sp_fib_entry {void* type; } ;
struct mlxsw_sp {int dummy; } ;
struct fib_info {struct net_device* fib_dev; } ;
struct fib_entry_notifier_info {int type; struct fib_info* fi; int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_UP ; 
 void* MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP ; 
 void* MLXSW_SP_FIB_ENTRY_TYPE_LOCAL ; 
 void* MLXSW_SP_FIB_ENTRY_TYPE_REMOTE ; 
 void* MLXSW_SP_FIB_ENTRY_TYPE_TRAP ; 
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV4 ; 
#define  RTN_BLACKHOLE 133 
#define  RTN_BROADCAST 132 
#define  RTN_LOCAL 131 
#define  RTN_PROHIBIT 130 
#define  RTN_UNICAST 129 
#define  RTN_UNREACHABLE 128 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fi_is_gateway (struct mlxsw_sp*,struct fib_info*) ; 
 int mlxsw_sp_fib_entry_decap_init (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,struct mlxsw_sp_ipip_entry*) ; 
 struct mlxsw_sp_ipip_entry* mlxsw_sp_ipip_entry_find_by_decap (struct mlxsw_sp*,struct net_device*,int /*<<< orphan*/ ,union mlxsw_sp_l3addr) ; 

__attribute__((used)) static int
mlxsw_sp_fib4_entry_type_set(struct mlxsw_sp *mlxsw_sp,
			     const struct fib_entry_notifier_info *fen_info,
			     struct mlxsw_sp_fib_entry *fib_entry)
{
	union mlxsw_sp_l3addr dip = { .addr4 = htonl(fen_info->dst) };
	struct net_device *dev = fen_info->fi->fib_dev;
	struct mlxsw_sp_ipip_entry *ipip_entry;
	struct fib_info *fi = fen_info->fi;

	switch (fen_info->type) {
	case RTN_LOCAL:
		ipip_entry = mlxsw_sp_ipip_entry_find_by_decap(mlxsw_sp, dev,
						 MLXSW_SP_L3_PROTO_IPV4, dip);
		if (ipip_entry && ipip_entry->ol_dev->flags & IFF_UP) {
			fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP;
			return mlxsw_sp_fib_entry_decap_init(mlxsw_sp,
							     fib_entry,
							     ipip_entry);
		}
		/* fall through */
	case RTN_BROADCAST:
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_TRAP;
		return 0;
	case RTN_UNREACHABLE: /* fall through */
	case RTN_BLACKHOLE: /* fall through */
	case RTN_PROHIBIT:
		/* Packets hitting these routes need to be trapped, but
		 * can do so with a lower priority than packets directed
		 * at the host, so use action type local instead of trap.
		 */
		fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_LOCAL;
		return 0;
	case RTN_UNICAST:
		if (mlxsw_sp_fi_is_gateway(mlxsw_sp, fi))
			fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_REMOTE;
		else
			fib_entry->type = MLXSW_SP_FIB_ENTRY_TYPE_LOCAL;
		return 0;
	default:
		return -EINVAL;
	}
}