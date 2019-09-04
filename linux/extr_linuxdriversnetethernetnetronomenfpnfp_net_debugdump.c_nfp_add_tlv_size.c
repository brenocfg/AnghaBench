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
typedef  int u32 ;
struct nfp_pf {int /*<<< orphan*/  hwinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  dump_length; } ;
struct nfp_dumpspec_csr {TYPE_1__ cpp; } ;
struct nfp_dump_tl {int /*<<< orphan*/  type; } ;
struct nfp_dump_csr {int dummy; } ;

/* Variables and functions */
 int ALIGN8 (int) ; 
#define  NFP_DUMPSPEC_TYPE_CPP_CSR 135 
#define  NFP_DUMPSPEC_TYPE_FWNAME 134 
#define  NFP_DUMPSPEC_TYPE_HWINFO 133 
#define  NFP_DUMPSPEC_TYPE_HWINFO_FIELD 132 
#define  NFP_DUMPSPEC_TYPE_INDIRECT_ME_CSR 131 
#define  NFP_DUMPSPEC_TYPE_ME_CSR 130 
#define  NFP_DUMPSPEC_TYPE_RTSYM 129 
#define  NFP_DUMPSPEC_TYPE_XPB_CSR 128 
 int NFP_IND_NUM_CONTEXTS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int nfp_calc_fwname_tlv_size (struct nfp_pf*) ; 
 int nfp_calc_hwinfo_field_sz (struct nfp_pf*,struct nfp_dump_tl*) ; 
 int nfp_calc_rtsym_dump_sz (struct nfp_pf*,struct nfp_dump_tl*) ; 
 int /*<<< orphan*/  nfp_csr_spec_valid (struct nfp_dumpspec_csr*) ; 
 int nfp_dump_error_tlv_size (struct nfp_dump_tl*) ; 
 int nfp_hwinfo_get_packed_str_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_add_tlv_size(struct nfp_pf *pf, struct nfp_dump_tl *tl, void *param)
{
	struct nfp_dumpspec_csr *spec_csr;
	u32 *size = param;
	u32 hwinfo_size;

	switch (be32_to_cpu(tl->type)) {
	case NFP_DUMPSPEC_TYPE_FWNAME:
		*size += nfp_calc_fwname_tlv_size(pf);
		break;
	case NFP_DUMPSPEC_TYPE_CPP_CSR:
	case NFP_DUMPSPEC_TYPE_XPB_CSR:
	case NFP_DUMPSPEC_TYPE_ME_CSR:
		spec_csr = (struct nfp_dumpspec_csr *)tl;
		if (!nfp_csr_spec_valid(spec_csr))
			*size += nfp_dump_error_tlv_size(tl);
		else
			*size += ALIGN8(sizeof(struct nfp_dump_csr)) +
				 ALIGN8(be32_to_cpu(spec_csr->cpp.dump_length));
		break;
	case NFP_DUMPSPEC_TYPE_INDIRECT_ME_CSR:
		spec_csr = (struct nfp_dumpspec_csr *)tl;
		if (!nfp_csr_spec_valid(spec_csr))
			*size += nfp_dump_error_tlv_size(tl);
		else
			*size += ALIGN8(sizeof(struct nfp_dump_csr)) +
				 ALIGN8(be32_to_cpu(spec_csr->cpp.dump_length) *
					NFP_IND_NUM_CONTEXTS);
		break;
	case NFP_DUMPSPEC_TYPE_RTSYM:
		*size += nfp_calc_rtsym_dump_sz(pf, tl);
		break;
	case NFP_DUMPSPEC_TYPE_HWINFO:
		hwinfo_size = nfp_hwinfo_get_packed_str_size(pf->hwinfo);
		*size += sizeof(struct nfp_dump_tl) + ALIGN8(hwinfo_size);
		break;
	case NFP_DUMPSPEC_TYPE_HWINFO_FIELD:
		*size += nfp_calc_hwinfo_field_sz(pf, tl);
		break;
	default:
		*size += nfp_dump_error_tlv_size(tl);
		break;
	}

	return 0;
}