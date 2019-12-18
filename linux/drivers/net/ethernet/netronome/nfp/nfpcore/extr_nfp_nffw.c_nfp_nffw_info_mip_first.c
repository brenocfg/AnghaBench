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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfp_nffw_info {int /*<<< orphan*/  cpp; } ;
struct nffw_fwinfo {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NFP_MU_ADDR_ACCESS_TYPE_DIRECT ; 
 int NFP_MU_ADDR_ACCESS_TYPE_MASK ; 
 int /*<<< orphan*/  nffw_fwinfo_mip_cppid_get (struct nffw_fwinfo*) ; 
 scalar_t__ nffw_fwinfo_mip_mu_da_get (struct nffw_fwinfo*) ; 
 int nffw_fwinfo_mip_offset_get (struct nffw_fwinfo*) ; 
 int nfp_cpp_mu_locality_lsb (int /*<<< orphan*/ ) ; 
 struct nffw_fwinfo* nfp_nffw_info_fwid_first (struct nfp_nffw_info*) ; 

int nfp_nffw_info_mip_first(struct nfp_nffw_info *state, u32 *cpp_id, u64 *off)
{
	struct nffw_fwinfo *fwinfo;

	fwinfo = nfp_nffw_info_fwid_first(state);
	if (!fwinfo)
		return -EINVAL;

	*cpp_id = nffw_fwinfo_mip_cppid_get(fwinfo);
	*off = nffw_fwinfo_mip_offset_get(fwinfo);

	if (nffw_fwinfo_mip_mu_da_get(fwinfo)) {
		int locality_off = nfp_cpp_mu_locality_lsb(state->cpp);

		*off &= ~(NFP_MU_ADDR_ACCESS_TYPE_MASK << locality_off);
		*off |= NFP_MU_ADDR_ACCESS_TYPE_DIRECT << locality_off;
	}

	return 0;
}