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
 int /*<<< orphan*/  NFP6000_ARM_GCSR_SOFTMODEL0 ; 
 int NFP_CPP_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_CPP_TARGET_ARM ; 
 scalar_t__ NFP_PL_DEVICE_ID ; 
 int NFP_PL_DEVICE_ID_MASK ; 
 scalar_t__ NFP_XPB_DEVICE (int,int,int) ; 
 int nfp_cpp_readl (struct nfp_cpp*,int const,int /*<<< orphan*/ ,int*) ; 
 int nfp_xpb_readl (struct nfp_cpp*,scalar_t__,int*) ; 

int nfp_cpp_model_autodetect(struct nfp_cpp *cpp, u32 *model)
{
	const u32 arm_id = NFP_CPP_ID(NFP_CPP_TARGET_ARM, 0, 0);
	u32 reg;
	int err;

	err = nfp_cpp_readl(cpp, arm_id, NFP6000_ARM_GCSR_SOFTMODEL0, model);
	if (err < 0)
		return err;

	/* The PL's PluDeviceID revision code is authoratative */
	*model &= ~0xff;
	err = nfp_xpb_readl(cpp, NFP_XPB_DEVICE(1, 1, 16) + NFP_PL_DEVICE_ID,
			    &reg);
	if (err < 0)
		return err;

	*model |= (NFP_PL_DEVICE_ID_MASK & reg) - 0x10;

	return 0;
}