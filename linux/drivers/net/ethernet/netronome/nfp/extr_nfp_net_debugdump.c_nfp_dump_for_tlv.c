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
struct nfp_pf {int dummy; } ;
struct nfp_dumpspec_rtsym {int dummy; } ;
struct nfp_dumpspec_csr {int dummy; } ;
struct nfp_dump_tl {int /*<<< orphan*/  type; } ;
struct nfp_dump_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
#define  NFP_DUMPSPEC_TYPE_CPP_CSR 135 
#define  NFP_DUMPSPEC_TYPE_FWNAME 134 
#define  NFP_DUMPSPEC_TYPE_HWINFO 133 
#define  NFP_DUMPSPEC_TYPE_HWINFO_FIELD 132 
#define  NFP_DUMPSPEC_TYPE_INDIRECT_ME_CSR 131 
#define  NFP_DUMPSPEC_TYPE_ME_CSR 130 
#define  NFP_DUMPSPEC_TYPE_RTSYM 129 
#define  NFP_DUMPSPEC_TYPE_XPB_CSR 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int nfp_dump_csr_range (struct nfp_pf*,struct nfp_dumpspec_csr*,struct nfp_dump_state*) ; 
 int nfp_dump_error_tlv (struct nfp_dump_tl*,int /*<<< orphan*/ ,struct nfp_dump_state*) ; 
 int nfp_dump_fwname (struct nfp_pf*,struct nfp_dump_state*) ; 
 int nfp_dump_hwinfo (struct nfp_pf*,struct nfp_dump_tl*,struct nfp_dump_state*) ; 
 int nfp_dump_hwinfo_field (struct nfp_pf*,struct nfp_dump_tl*,struct nfp_dump_state*) ; 
 int nfp_dump_indirect_csr_range (struct nfp_pf*,struct nfp_dumpspec_csr*,struct nfp_dump_state*) ; 
 int nfp_dump_single_rtsym (struct nfp_pf*,struct nfp_dumpspec_rtsym*,struct nfp_dump_state*) ; 

__attribute__((used)) static int
nfp_dump_for_tlv(struct nfp_pf *pf, struct nfp_dump_tl *tl, void *param)
{
	struct nfp_dumpspec_rtsym *spec_rtsym;
	struct nfp_dump_state *dump = param;
	struct nfp_dumpspec_csr *spec_csr;
	int err;

	switch (be32_to_cpu(tl->type)) {
	case NFP_DUMPSPEC_TYPE_FWNAME:
		err = nfp_dump_fwname(pf, dump);
		if (err)
			return err;
		break;
	case NFP_DUMPSPEC_TYPE_CPP_CSR:
	case NFP_DUMPSPEC_TYPE_XPB_CSR:
	case NFP_DUMPSPEC_TYPE_ME_CSR:
		spec_csr = (struct nfp_dumpspec_csr *)tl;
		err = nfp_dump_csr_range(pf, spec_csr, dump);
		if (err)
			return err;
		break;
	case NFP_DUMPSPEC_TYPE_INDIRECT_ME_CSR:
		spec_csr = (struct nfp_dumpspec_csr *)tl;
		err = nfp_dump_indirect_csr_range(pf, spec_csr, dump);
		if (err)
			return err;
		break;
	case NFP_DUMPSPEC_TYPE_RTSYM:
		spec_rtsym = (struct nfp_dumpspec_rtsym *)tl;
		err = nfp_dump_single_rtsym(pf, spec_rtsym, dump);
		if (err)
			return err;
		break;
	case NFP_DUMPSPEC_TYPE_HWINFO:
		err = nfp_dump_hwinfo(pf, tl, dump);
		if (err)
			return err;
		break;
	case NFP_DUMPSPEC_TYPE_HWINFO_FIELD:
		err = nfp_dump_hwinfo_field(pf, tl, dump);
		if (err)
			return err;
		break;
	default:
		err = nfp_dump_error_tlv(tl, -EOPNOTSUPP, dump);
		if (err)
			return err;
	}

	return 0;
}