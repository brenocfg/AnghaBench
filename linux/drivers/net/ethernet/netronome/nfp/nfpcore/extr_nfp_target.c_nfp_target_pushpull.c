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

/* Variables and functions */
 int EINVAL ; 
 int NFP_CPP_ID_TARGET_of (int /*<<< orphan*/ ) ; 
#define  NFP_CPP_TARGET_ARM 136 
#define  NFP_CPP_TARGET_CLS 135 
#define  NFP_CPP_TARGET_CRYPTO 134 
#define  NFP_CPP_TARGET_CT_XPB 133 
#define  NFP_CPP_TARGET_ILA 132 
#define  NFP_CPP_TARGET_MU 131 
#define  NFP_CPP_TARGET_NBI 130 
#define  NFP_CPP_TARGET_PCIE 129 
#define  NFP_CPP_TARGET_QDR 128 
 int /*<<< orphan*/  P32 ; 
 int /*<<< orphan*/  P64 ; 
 int nfp6000_cap_xpb (int /*<<< orphan*/ ) ; 
 int nfp6000_cls (int /*<<< orphan*/ ) ; 
 int nfp6000_crypto (int /*<<< orphan*/ ) ; 
 int nfp6000_ila (int /*<<< orphan*/ ) ; 
 int nfp6000_mu (int /*<<< orphan*/ ,int) ; 
 int nfp6000_nbi (int /*<<< orphan*/ ,int) ; 
 int nfp6000_pci (int /*<<< orphan*/ ) ; 
 int target_rw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int nfp_target_pushpull(u32 cpp_id, u64 address)
{
	switch (NFP_CPP_ID_TARGET_of(cpp_id)) {
	case NFP_CPP_TARGET_NBI:
		return nfp6000_nbi(cpp_id, address);
	case NFP_CPP_TARGET_QDR:
		return target_rw(cpp_id, P32, 24, 4);
	case NFP_CPP_TARGET_ILA:
		return nfp6000_ila(cpp_id);
	case NFP_CPP_TARGET_MU:
		return nfp6000_mu(cpp_id, address);
	case NFP_CPP_TARGET_PCIE:
		return nfp6000_pci(cpp_id);
	case NFP_CPP_TARGET_ARM:
		if (address < 0x10000)
			return target_rw(cpp_id, P64, 1, 1);
		else
			return target_rw(cpp_id, P32, 1, 1);
	case NFP_CPP_TARGET_CRYPTO:
		return nfp6000_crypto(cpp_id);
	case NFP_CPP_TARGET_CT_XPB:
		return nfp6000_cap_xpb(cpp_id);
	case NFP_CPP_TARGET_CLS:
		return nfp6000_cls(cpp_id);
	case 0:
		return target_rw(cpp_id, P32, 4, 4);
	default:
		return -EINVAL;
	}
}