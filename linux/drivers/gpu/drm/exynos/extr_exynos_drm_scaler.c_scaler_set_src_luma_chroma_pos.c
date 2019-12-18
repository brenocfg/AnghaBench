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
struct scaler_format {int chroma_tile_w; int chroma_tile_h; } ;
struct scaler_context {int dummy; } ;
struct drm_exynos_ipp_task_rect {int x; int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALER_SRC_C_POS ; 
 int /*<<< orphan*/  SCALER_SRC_C_POS_SET_CH_POS (int) ; 
 int /*<<< orphan*/  SCALER_SRC_C_POS_SET_CV_POS (int) ; 
 int /*<<< orphan*/  SCALER_SRC_Y_POS ; 
 int /*<<< orphan*/  SCALER_SRC_Y_POS_SET_YH_POS (int) ; 
 int /*<<< orphan*/  SCALER_SRC_Y_POS_SET_YV_POS (int) ; 
 int /*<<< orphan*/  scaler_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void scaler_set_src_luma_chroma_pos(struct scaler_context *scaler,
			struct drm_exynos_ipp_task_rect *src_pos,
			const struct scaler_format *fmt)
{
	u32 val;

	val = SCALER_SRC_Y_POS_SET_YH_POS(src_pos->x << 2);
	val |=  SCALER_SRC_Y_POS_SET_YV_POS(src_pos->y << 2);
	scaler_write(val, SCALER_SRC_Y_POS);
	val = SCALER_SRC_C_POS_SET_CH_POS(
		(src_pos->x * fmt->chroma_tile_w / 16) << 2);
	val |=  SCALER_SRC_C_POS_SET_CV_POS(
		(src_pos->y * fmt->chroma_tile_h / 16) << 2);
	scaler_write(val, SCALER_SRC_C_POS);
}