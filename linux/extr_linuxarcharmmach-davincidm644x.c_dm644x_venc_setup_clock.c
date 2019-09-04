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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum vpbe_enc_timings_type { ____Placeholder_vpbe_enc_timings_type } vpbe_enc_timings_type ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_SYSMOD_VIRT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM644X_VPSS_DACCLKEN ; 
 int /*<<< orphan*/  DM644X_VPSS_MUXSEL_VPBECLK_MODE ; 
 int /*<<< orphan*/  DM644X_VPSS_VENCLKEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  SYSMOD_VPSS_CLKCTL ; 
#define  VPBE_ENC_DV_TIMINGS 129 
#define  VPBE_ENC_STD 128 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm644x_venc_setup_clock(enum vpbe_enc_timings_type type,
				   unsigned int pclock)
{
	int ret = 0;
	u32 v = DM644X_VPSS_VENCLKEN;

	switch (type) {
	case VPBE_ENC_STD:
		v |= DM644X_VPSS_DACCLKEN;
		writel(v, DAVINCI_SYSMOD_VIRT(SYSMOD_VPSS_CLKCTL));
		break;
	case VPBE_ENC_DV_TIMINGS:
		if (pclock <= 27000000) {
			v |= DM644X_VPSS_DACCLKEN;
			writel(v, DAVINCI_SYSMOD_VIRT(SYSMOD_VPSS_CLKCTL));
		} else {
			/*
			 * For HD, use external clock source since
			 * HD requires higher clock rate
			 */
			v |= DM644X_VPSS_MUXSEL_VPBECLK_MODE;
			writel(v, DAVINCI_SYSMOD_VIRT(SYSMOD_VPSS_CLKCTL));
		}
		break;
	default:
		ret  = -EINVAL;
	}

	return ret;
}