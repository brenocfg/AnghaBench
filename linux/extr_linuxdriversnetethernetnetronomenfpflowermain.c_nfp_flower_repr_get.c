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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfp_reprs {size_t num_reprs; int /*<<< orphan*/ * reprs; } ;
struct nfp_app {int /*<<< orphan*/ * reprs; } ;
struct net_device {size_t num_reprs; int /*<<< orphan*/ * reprs; } ;
typedef  enum nfp_repr_type { ____Placeholder_nfp_repr_type } nfp_repr_type ;

/* Variables and functions */
 int NFP_REPR_TYPE_MAX ; 
 int nfp_flower_repr_get_type_and_port (struct nfp_app*,int /*<<< orphan*/ ,size_t*) ; 
 struct nfp_reprs* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *
nfp_flower_repr_get(struct nfp_app *app, u32 port_id)
{
	enum nfp_repr_type repr_type;
	struct nfp_reprs *reprs;
	u8 port = 0;

	repr_type = nfp_flower_repr_get_type_and_port(app, port_id, &port);
	if (repr_type > NFP_REPR_TYPE_MAX)
		return NULL;

	reprs = rcu_dereference(app->reprs[repr_type]);
	if (!reprs)
		return NULL;

	if (port >= reprs->num_reprs)
		return NULL;

	return rcu_dereference(reprs->reprs[port]);
}