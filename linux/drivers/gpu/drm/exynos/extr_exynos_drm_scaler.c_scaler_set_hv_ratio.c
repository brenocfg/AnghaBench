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
struct scaler_context {int dummy; } ;
struct drm_exynos_ipp_task_rect {int h; int w; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALER_H_RATIO ; 
 int SCALER_H_RATIO_SET (int) ; 
 int /*<<< orphan*/  SCALER_V_RATIO ; 
 int SCALER_V_RATIO_SET (int) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 int /*<<< orphan*/  scaler_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void scaler_set_hv_ratio(struct scaler_context *scaler,
	unsigned int rotation,
	struct drm_exynos_ipp_task_rect *src_pos,
	struct drm_exynos_ipp_task_rect *dst_pos)
{
	u32 val, h_ratio, v_ratio;

	if (drm_rotation_90_or_270(rotation)) {
		h_ratio = (src_pos->h << 16) / dst_pos->w;
		v_ratio = (src_pos->w << 16) / dst_pos->h;
	} else {
		h_ratio = (src_pos->w << 16) / dst_pos->w;
		v_ratio = (src_pos->h << 16) / dst_pos->h;
	}

	val = SCALER_H_RATIO_SET(h_ratio);
	scaler_write(val, SCALER_H_RATIO);

	val = SCALER_V_RATIO_SET(v_ratio);
	scaler_write(val, SCALER_V_RATIO);
}