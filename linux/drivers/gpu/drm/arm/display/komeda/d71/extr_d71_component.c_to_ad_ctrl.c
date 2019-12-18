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
 int /*<<< orphan*/  AD_AEN ; 
 int /*<<< orphan*/  AD_BS ; 
 int /*<<< orphan*/  AD_TH ; 
 int /*<<< orphan*/  AD_WB ; 
 int /*<<< orphan*/  AD_YT ; 
 int AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 ; 
 int AFBC_FORMAT_MOD_BLOCK_SIZE_MASK ; 
 int AFBC_FORMAT_MOD_SPLIT ; 
 int AFBC_FORMAT_MOD_TILED ; 
 int AFBC_FORMAT_MOD_YTR ; 

__attribute__((used)) static u32 to_ad_ctrl(u64 modifier)
{
	u32 afbc_ctrl = AD_AEN;

	if (!modifier)
		return 0;

	if ((modifier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK) ==
	    AFBC_FORMAT_MOD_BLOCK_SIZE_32x8)
		afbc_ctrl |= AD_WB;

	if (modifier & AFBC_FORMAT_MOD_YTR)
		afbc_ctrl |= AD_YT;
	if (modifier & AFBC_FORMAT_MOD_SPLIT)
		afbc_ctrl |= AD_BS;
	if (modifier & AFBC_FORMAT_MOD_TILED)
		afbc_ctrl |= AD_TH;

	return afbc_ctrl;
}