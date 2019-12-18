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
struct nfp_abm_link {int dummy; } ;
struct nfp_abm {int /*<<< orphan*/  app; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_REPR_TYPE_PF ; 
 int /*<<< orphan*/  NFP_REPR_TYPE_PHYS_PORT ; 
 int /*<<< orphan*/  nfp_abm_kill_repr (int /*<<< orphan*/ ,struct nfp_abm_link*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_abm_kill_reprs(struct nfp_abm *abm, struct nfp_abm_link *alink)
{
	nfp_abm_kill_repr(abm->app, alink, NFP_REPR_TYPE_PF);
	nfp_abm_kill_repr(abm->app, alink, NFP_REPR_TYPE_PHYS_PORT);
}