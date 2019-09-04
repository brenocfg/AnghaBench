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
struct scaler_context {int dummy; } ;

/* Variables and functions */
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 unsigned int DRM_MODE_ROTATE_270 ; 
 unsigned int DRM_MODE_ROTATE_90 ; 
 int /*<<< orphan*/  SCALER_ROT_CFG ; 
 int /*<<< orphan*/  SCALER_ROT_CFG_FLIP_X_EN ; 
 int /*<<< orphan*/  SCALER_ROT_CFG_FLIP_Y_EN ; 
 int /*<<< orphan*/  SCALER_ROT_CFG_SET_ROTMODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALER_ROT_MODE_180 ; 
 int /*<<< orphan*/  SCALER_ROT_MODE_270 ; 
 int /*<<< orphan*/  SCALER_ROT_MODE_90 ; 
 int /*<<< orphan*/  scaler_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void scaler_set_rotation(struct scaler_context *scaler,
	unsigned int rotation)
{
	u32 val = 0;

	if (rotation & DRM_MODE_ROTATE_90)
		val |= SCALER_ROT_CFG_SET_ROTMODE(SCALER_ROT_MODE_90);
	else if (rotation & DRM_MODE_ROTATE_180)
		val |= SCALER_ROT_CFG_SET_ROTMODE(SCALER_ROT_MODE_180);
	else if (rotation & DRM_MODE_ROTATE_270)
		val |= SCALER_ROT_CFG_SET_ROTMODE(SCALER_ROT_MODE_270);
	if (rotation & DRM_MODE_REFLECT_X)
		val |= SCALER_ROT_CFG_FLIP_X_EN;
	if (rotation & DRM_MODE_REFLECT_Y)
		val |= SCALER_ROT_CFG_FLIP_Y_EN;
	scaler_write(val, SCALER_ROT_CFG);
}