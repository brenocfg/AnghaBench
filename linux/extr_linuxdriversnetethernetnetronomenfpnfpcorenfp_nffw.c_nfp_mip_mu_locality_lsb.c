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
typedef  int u32 ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int NFP_CPP_TARGET_MU ; 
 int NFP_IMB_TGTADDRESSMODECFG_ADDRMODE ; 
 unsigned int NFP_IMB_TGTADDRESSMODECFG_MODE_of (int) ; 
 int nfp_cppat_mu_locality_lsb (unsigned int,unsigned int) ; 
 int nfp_xpb_readl (struct nfp_cpp*,int,int*) ; 

__attribute__((used)) static int nfp_mip_mu_locality_lsb(struct nfp_cpp *cpp)
{
	unsigned int mode, addr40;
	u32 xpbaddr, imbcppat;
	int err;

	/* Hardcoded XPB IMB Base, island 0 */
	xpbaddr = 0x000a0000 + NFP_CPP_TARGET_MU * 4;
	err = nfp_xpb_readl(cpp, xpbaddr, &imbcppat);
	if (err < 0)
		return err;

	mode = NFP_IMB_TGTADDRESSMODECFG_MODE_of(imbcppat);
	addr40 = !!(imbcppat & NFP_IMB_TGTADDRESSMODECFG_ADDRMODE);

	return nfp_cppat_mu_locality_lsb(mode, addr40);
}