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
struct drm_dp_aux {int /*<<< orphan*/  crc_work; struct drm_crtc* crtc; scalar_t__ crc_count; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TEST_SINK ; 
 int DP_TEST_SINK_START ; 
 int drm_dp_dpcd_readb (struct drm_dp_aux*,int /*<<< orphan*/ ,int*) ; 
 int drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int drm_dp_start_crc(struct drm_dp_aux *aux, struct drm_crtc *crtc)
{
	u8 buf;
	int ret;

	ret = drm_dp_dpcd_readb(aux, DP_TEST_SINK, &buf);
	if (ret < 0)
		return ret;

	ret = drm_dp_dpcd_writeb(aux, DP_TEST_SINK, buf | DP_TEST_SINK_START);
	if (ret < 0)
		return ret;

	aux->crc_count = 0;
	aux->crtc = crtc;
	schedule_work(&aux->crc_work);

	return 0;
}