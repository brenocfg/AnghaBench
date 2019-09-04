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
struct nfp_abm_link {int /*<<< orphan*/  qdiscs; int /*<<< orphan*/  abm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfp_abm_link*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_kill_reprs (int /*<<< orphan*/ ,struct nfp_abm_link*) ; 

__attribute__((used)) static void nfp_abm_vnic_free(struct nfp_app *app, struct nfp_net *nn)
{
	struct nfp_abm_link *alink = nn->app_priv;

	nfp_abm_kill_reprs(alink->abm, alink);
	kvfree(alink->qdiscs);
	kfree(alink);
}