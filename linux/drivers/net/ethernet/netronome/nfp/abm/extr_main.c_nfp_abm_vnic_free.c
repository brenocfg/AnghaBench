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
struct nfp_abm_link {struct nfp_abm_link* prio_map; int /*<<< orphan*/  qdiscs; int /*<<< orphan*/  abm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  kfree (struct nfp_abm_link*) ; 
 int /*<<< orphan*/  nfp_abm_kill_reprs (int /*<<< orphan*/ ,struct nfp_abm_link*) ; 
 int /*<<< orphan*/  radix_tree_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_abm_vnic_free(struct nfp_app *app, struct nfp_net *nn)
{
	struct nfp_abm_link *alink = nn->app_priv;

	nfp_abm_kill_reprs(alink->abm, alink);
	WARN(!radix_tree_empty(&alink->qdiscs), "left over qdiscs\n");
	kfree(alink->prio_map);
	kfree(alink);
}