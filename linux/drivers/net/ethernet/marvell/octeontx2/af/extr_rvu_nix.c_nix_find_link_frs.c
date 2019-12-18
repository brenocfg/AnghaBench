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
typedef  int /*<<< orphan*/  u16 ;
struct rvu_pfvf {int maxlen; int minlen; } ;
struct rvu {struct rvu_pfvf* pf; struct rvu_pfvf* hwvf; } ;
struct nix_frs_cfg {int maxlen; int minlen; scalar_t__ update_minlen; } ;

/* Variables and functions */
 int rvu_get_pf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_get_pf_numvfs (struct rvu*,int,int*,int*) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nix_find_link_frs(struct rvu *rvu,
			      struct nix_frs_cfg *req, u16 pcifunc)
{
	int pf = rvu_get_pf(pcifunc);
	struct rvu_pfvf *pfvf;
	int maxlen, minlen;
	int numvfs, hwvf;
	int vf;

	/* Update with requester's min/max lengths */
	pfvf = rvu_get_pfvf(rvu, pcifunc);
	pfvf->maxlen = req->maxlen;
	if (req->update_minlen)
		pfvf->minlen = req->minlen;

	maxlen = req->maxlen;
	minlen = req->update_minlen ? req->minlen : 0;

	/* Get this PF's numVFs and starting hwvf */
	rvu_get_pf_numvfs(rvu, pf, &numvfs, &hwvf);

	/* For each VF, compare requested max/minlen */
	for (vf = 0; vf < numvfs; vf++) {
		pfvf =  &rvu->hwvf[hwvf + vf];
		if (pfvf->maxlen > maxlen)
			maxlen = pfvf->maxlen;
		if (req->update_minlen &&
		    pfvf->minlen && pfvf->minlen < minlen)
			minlen = pfvf->minlen;
	}

	/* Compare requested max/minlen with PF's max/minlen */
	pfvf = &rvu->pf[pf];
	if (pfvf->maxlen > maxlen)
		maxlen = pfvf->maxlen;
	if (req->update_minlen &&
	    pfvf->minlen && pfvf->minlen < minlen)
		minlen = pfvf->minlen;

	/* Update the request with max/min PF's and it's VF's max/min */
	req->maxlen = maxlen;
	if (req->update_minlen)
		req->minlen = minlen;
}