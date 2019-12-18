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
struct nfp_net {struct nfp_abm_link* app_priv; } ;
struct nfp_app {int dummy; } ;
struct nfp_abm_link {int /*<<< orphan*/  prio_map; int /*<<< orphan*/  abm; } ;

/* Variables and functions */
 int nfp_abm_ctrl_prio_map_update (struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfp_abm_has_prio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_abm_vnic_init(struct nfp_app *app, struct nfp_net *nn)
{
	struct nfp_abm_link *alink = nn->app_priv;

	if (nfp_abm_has_prio(alink->abm))
		return nfp_abm_ctrl_prio_map_update(alink, alink->prio_map);
	return 0;
}