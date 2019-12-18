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
typedef  int /*<<< orphan*/  u8 ;
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_MAIN_LINK_CHANNEL_CODING_SET ; 
 int drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_dp_aux_prepare(struct drm_dp_aux *aux, u8 encoding)
{
	int err;

	err = drm_dp_dpcd_writeb(aux, DP_MAIN_LINK_CHANNEL_CODING_SET,
				 encoding);
	if (err < 0)
		return err;

	return 0;
}