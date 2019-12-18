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
 void* FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_ABM_PORTID_ID ; 
 int /*<<< orphan*/  NFP_ABM_PORTID_TYPE ; 
 struct nfp_reprs* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *
nfp_abm_repr_get(struct nfp_app *app, u32 port_id, bool *redir_egress)
{
	enum nfp_repr_type rtype;
	struct nfp_reprs *reprs;
	u8 port;

	rtype = FIELD_GET(NFP_ABM_PORTID_TYPE, port_id);
	port = FIELD_GET(NFP_ABM_PORTID_ID, port_id);

	reprs = rcu_dereference(app->reprs[rtype]);
	if (!reprs)
		return NULL;

	if (port >= reprs->num_reprs)
		return NULL;

	return rcu_dereference(reprs->reprs[port]);
}