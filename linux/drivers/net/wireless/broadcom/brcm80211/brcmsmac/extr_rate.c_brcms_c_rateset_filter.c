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
typedef  size_t uint ;
typedef  scalar_t__ u8 ;
struct brcms_c_rateset {size_t count; size_t* rates; int /*<<< orphan*/ * mcs; int /*<<< orphan*/  htphy_membership; } ;

/* Variables and functions */
 scalar_t__ BRCMS_RATES_CCK ; 
 scalar_t__ BRCMS_RATES_OFDM ; 
 size_t BRCMS_RATE_FLAG ; 
 size_t BRCMS_RATE_MASK ; 
 int /*<<< orphan*/  MCSSET_LEN ; 
 int /*<<< orphan*/  brcms_c_rateset_mcs_clear (struct brcms_c_rateset*) ; 
 scalar_t__ is_cck_rate (size_t) ; 
 scalar_t__ is_ofdm_rate (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
brcms_c_rateset_filter(struct brcms_c_rateset *src, struct brcms_c_rateset *dst,
		       bool basic_only, u8 rates, uint xmask, bool mcsallow)
{
	uint i;
	uint r;
	uint count;

	count = 0;
	for (i = 0; i < src->count; i++) {
		r = src->rates[i];
		if (basic_only && !(r & BRCMS_RATE_FLAG))
			continue;
		if (rates == BRCMS_RATES_CCK &&
		    is_ofdm_rate((r & BRCMS_RATE_MASK)))
			continue;
		if (rates == BRCMS_RATES_OFDM &&
		    is_cck_rate((r & BRCMS_RATE_MASK)))
			continue;
		dst->rates[count++] = r & xmask;
	}
	dst->count = count;
	dst->htphy_membership = src->htphy_membership;

	if (mcsallow && rates != BRCMS_RATES_CCK)
		memcpy(&dst->mcs[0], &src->mcs[0], MCSSET_LEN);
	else
		brcms_c_rateset_mcs_clear(dst);
}