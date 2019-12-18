#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long long u64 ;
typedef  int u16 ;
struct rvu {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int eol; int pf_func; int next; scalar_t__ index; scalar_t__ op; } ;
struct TYPE_3__ {scalar_t__ pcifunc; } ;
struct nix_aq_enq_req {int qidx; int /*<<< orphan*/  mce_mask; TYPE_2__ mce; int /*<<< orphan*/  op; int /*<<< orphan*/  ctype; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIX_AQ_CTYPE_MCE ; 
 int RVU_PFVF_FUNC_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rvu_get_pf (int) ; 
 int rvu_nix_aq_enq_inst (struct rvu*,struct nix_aq_enq_req*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nix_setup_mce(struct rvu *rvu, int mce, u8 op,
			 u16 pcifunc, int next, bool eol)
{
	struct nix_aq_enq_req aq_req;
	int err;

	aq_req.hdr.pcifunc = 0;
	aq_req.ctype = NIX_AQ_CTYPE_MCE;
	aq_req.op = op;
	aq_req.qidx = mce;

	/* Forward bcast pkts to RQ0, RSS not needed */
	aq_req.mce.op = 0;
	aq_req.mce.index = 0;
	aq_req.mce.eol = eol;
	aq_req.mce.pf_func = pcifunc;
	aq_req.mce.next = next;

	/* All fields valid */
	*(u64 *)(&aq_req.mce_mask) = ~0ULL;

	err = rvu_nix_aq_enq_inst(rvu, &aq_req, NULL);
	if (err) {
		dev_err(rvu->dev, "Failed to setup Bcast MCE for PF%d:VF%d\n",
			rvu_get_pf(pcifunc), pcifunc & RVU_PFVF_FUNC_MASK);
		return err;
	}
	return 0;
}