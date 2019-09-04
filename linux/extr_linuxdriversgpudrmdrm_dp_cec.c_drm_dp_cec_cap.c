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
typedef  int u8 ;
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_CEC_TUNNELING_CAPABILITY ; 
 int DP_CEC_TUNNELING_CAPABLE ; 
 int drm_dp_dpcd_readb (struct drm_dp_aux*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool drm_dp_cec_cap(struct drm_dp_aux *aux, u8 *cec_cap)
{
	u8 cap = 0;

	if (drm_dp_dpcd_readb(aux, DP_CEC_TUNNELING_CAPABILITY, &cap) != 1 ||
	    !(cap & DP_CEC_TUNNELING_CAPABLE))
		return false;
	if (cec_cap)
		*cec_cap = cap;
	return true;
}