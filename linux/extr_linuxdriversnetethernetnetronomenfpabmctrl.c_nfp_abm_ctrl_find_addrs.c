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
struct nfp_rtsym {int dummy; } ;
struct nfp_pf {int /*<<< orphan*/  cpp; } ;
struct nfp_abm {unsigned int pf_id; struct nfp_rtsym const* qm_stats; struct nfp_rtsym const* q_lvls; TYPE_1__* app; } ;
typedef  int /*<<< orphan*/  pf_symbol ;
struct TYPE_2__ {struct nfp_pf* pf; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfp_rtsym const*) ; 
 int /*<<< orphan*/  NFP_QLVL_STRIDE ; 
 char* NFP_QLVL_SYM_NAME ; 
 int /*<<< orphan*/  NFP_QMSTAT_STRIDE ; 
 char* NFP_QMSTAT_SYM_NAME ; 
 int PTR_ERR (struct nfp_rtsym const*) ; 
 struct nfp_rtsym* nfp_abm_ctrl_find_q_rtsym (struct nfp_pf*,char*,int /*<<< orphan*/ ) ; 
 unsigned int nfp_cppcore_pcie_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

int nfp_abm_ctrl_find_addrs(struct nfp_abm *abm)
{
	struct nfp_pf *pf = abm->app->pf;
	const struct nfp_rtsym *sym;
	unsigned int pf_id;
	char pf_symbol[64];

	pf_id =	nfp_cppcore_pcie_unit(pf->cpp);
	abm->pf_id = pf_id;

	snprintf(pf_symbol, sizeof(pf_symbol), NFP_QLVL_SYM_NAME, pf_id);
	sym = nfp_abm_ctrl_find_q_rtsym(pf, pf_symbol, NFP_QLVL_STRIDE);
	if (IS_ERR(sym))
		return PTR_ERR(sym);
	abm->q_lvls = sym;

	snprintf(pf_symbol, sizeof(pf_symbol), NFP_QMSTAT_SYM_NAME, pf_id);
	sym = nfp_abm_ctrl_find_q_rtsym(pf, pf_symbol, NFP_QMSTAT_STRIDE);
	if (IS_ERR(sym))
		return PTR_ERR(sym);
	abm->qm_stats = sym;

	return 0;
}