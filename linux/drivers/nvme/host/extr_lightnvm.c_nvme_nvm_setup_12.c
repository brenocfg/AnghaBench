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
struct nvme_nvm_id12_grp {scalar_t__ mtype; int num_ch; int num_lun; int num_pln; int /*<<< orphan*/  fpg_sz; int /*<<< orphan*/  num_pg; int /*<<< orphan*/  mpos; int /*<<< orphan*/  cpar; int /*<<< orphan*/  fmtype; int /*<<< orphan*/  tbem; int /*<<< orphan*/  tbet; int /*<<< orphan*/  tprm; int /*<<< orphan*/  tprt; int /*<<< orphan*/  trdm; int /*<<< orphan*/  trdt; int /*<<< orphan*/  mccap; int /*<<< orphan*/  sos; int /*<<< orphan*/  csecs; int /*<<< orphan*/  num_chk; } ;
struct nvme_nvm_id12 {int cgrps; int /*<<< orphan*/  ppaf; int /*<<< orphan*/  dom; int /*<<< orphan*/  cap; int /*<<< orphan*/  vmnt; int /*<<< orphan*/  ver_id; struct nvme_nvm_id12_grp grp; } ;
struct nvm_geo {int minor_ver_id; int num_ch; int num_lun; int all_luns; int num_chk; int csecs; int sos; int clba; int all_chunks; int total_secs; int ws_min; int ws_opt; int mw_cunits; int maxoc; int maxocpu; scalar_t__ mtype; int cpar; int mpos; int num_pln; int num_pg; int fpg_sz; int /*<<< orphan*/  addrf; int /*<<< orphan*/  pln_mode; int /*<<< orphan*/  fmtype; void* dom; void* cap; int /*<<< orphan*/  vmnt; void* tbem; void* tbet; void* tprm; void* tprt; void* trdm; void* trdt; void* mccap; int /*<<< orphan*/  version; int /*<<< orphan*/  major_ver_id; } ;
struct nvm_addrf_12 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NVM_OCSSD_SPEC_12 ; 
 int /*<<< orphan*/  NVM_PLANE_DOUBLE ; 
 int /*<<< orphan*/  NVM_PLANE_QUAD ; 
 int /*<<< orphan*/  NVM_PLANE_SINGLE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_nvm_set_addr_12 (struct nvm_addrf_12*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int nvme_nvm_setup_12(struct nvme_nvm_id12 *id,
			     struct nvm_geo *geo)
{
	struct nvme_nvm_id12_grp *src;
	int sec_per_pg, sec_per_pl, pg_per_blk;

	if (id->cgrps != 1)
		return -EINVAL;

	src = &id->grp;

	if (src->mtype != 0) {
		pr_err("nvm: memory type not supported\n");
		return -EINVAL;
	}

	/* 1.2 spec. only reports a single version id - unfold */
	geo->major_ver_id = id->ver_id;
	geo->minor_ver_id = 2;

	/* Set compacted version for upper layers */
	geo->version = NVM_OCSSD_SPEC_12;

	geo->num_ch = src->num_ch;
	geo->num_lun = src->num_lun;
	geo->all_luns = geo->num_ch * geo->num_lun;

	geo->num_chk = le16_to_cpu(src->num_chk);

	geo->csecs = le16_to_cpu(src->csecs);
	geo->sos = le16_to_cpu(src->sos);

	pg_per_blk = le16_to_cpu(src->num_pg);
	sec_per_pg = le16_to_cpu(src->fpg_sz) / geo->csecs;
	sec_per_pl = sec_per_pg * src->num_pln;
	geo->clba = sec_per_pl * pg_per_blk;

	geo->all_chunks = geo->all_luns * geo->num_chk;
	geo->total_secs = geo->clba * geo->all_chunks;

	geo->ws_min = sec_per_pg;
	geo->ws_opt = sec_per_pg;
	geo->mw_cunits = geo->ws_opt << 3;	/* default to MLC safe values */

	/* Do not impose values for maximum number of open blocks as it is
	 * unspecified in 1.2. Users of 1.2 must be aware of this and eventually
	 * specify these values through a quirk if restrictions apply.
	 */
	geo->maxoc = geo->all_luns * geo->num_chk;
	geo->maxocpu = geo->num_chk;

	geo->mccap = le32_to_cpu(src->mccap);

	geo->trdt = le32_to_cpu(src->trdt);
	geo->trdm = le32_to_cpu(src->trdm);
	geo->tprt = le32_to_cpu(src->tprt);
	geo->tprm = le32_to_cpu(src->tprm);
	geo->tbet = le32_to_cpu(src->tbet);
	geo->tbem = le32_to_cpu(src->tbem);

	/* 1.2 compatibility */
	geo->vmnt = id->vmnt;
	geo->cap = le32_to_cpu(id->cap);
	geo->dom = le32_to_cpu(id->dom);

	geo->mtype = src->mtype;
	geo->fmtype = src->fmtype;

	geo->cpar = le16_to_cpu(src->cpar);
	geo->mpos = le32_to_cpu(src->mpos);

	geo->pln_mode = NVM_PLANE_SINGLE;

	if (geo->mpos & 0x020202) {
		geo->pln_mode = NVM_PLANE_DOUBLE;
		geo->ws_opt <<= 1;
	} else if (geo->mpos & 0x040404) {
		geo->pln_mode = NVM_PLANE_QUAD;
		geo->ws_opt <<= 2;
	}

	geo->num_pln = src->num_pln;
	geo->num_pg = le16_to_cpu(src->num_pg);
	geo->fpg_sz = le16_to_cpu(src->fpg_sz);

	nvme_nvm_set_addr_12((struct nvm_addrf_12 *)&geo->addrf, &id->ppaf);

	return 0;
}