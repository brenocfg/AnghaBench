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
 scalar_t__ NFP_PL_DEVICE_ID ; 
 int NFP_PL_DEVICE_ID_MASK ; 
 int NFP_PL_DEVICE_MODEL_MASK ; 
 scalar_t__ NFP_XPB_DEVICE (int,int,int) ; 
 int nfp_xpb_readl (struct nfp_cpp*,scalar_t__,int*) ; 

int nfp_cpp_model_autodetect(struct nfp_cpp *cpp, u32 *model)
{
	u32 reg;
	int err;

	err = nfp_xpb_readl(cpp, NFP_XPB_DEVICE(1, 1, 16) + NFP_PL_DEVICE_ID,
			    &reg);
	if (err < 0)
		return err;

	*model = reg & NFP_PL_DEVICE_MODEL_MASK;
	if (*model & NFP_PL_DEVICE_ID_MASK)
		*model -= 0x10;

	return 0;
}