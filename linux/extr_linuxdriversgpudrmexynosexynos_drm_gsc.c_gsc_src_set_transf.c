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
struct gsc_context {int rotation; } ;

/* Variables and functions */
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 unsigned int DRM_MODE_ROTATE_MASK ; 
 int /*<<< orphan*/  GSC_IN_CON ; 
 int GSC_IN_ROT_180 ; 
 int GSC_IN_ROT_270 ; 
 int GSC_IN_ROT_90 ; 
 int GSC_IN_ROT_MASK ; 
 int GSC_IN_ROT_XFLIP ; 
 int GSC_IN_ROT_YFLIP ; 
 int gsc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsc_src_set_transf(struct gsc_context *ctx, unsigned int rotation)
{
	unsigned int degree = rotation & DRM_MODE_ROTATE_MASK;
	u32 cfg;

	cfg = gsc_read(GSC_IN_CON);
	cfg &= ~GSC_IN_ROT_MASK;

	switch (degree) {
	case DRM_MODE_ROTATE_0:
		if (rotation & DRM_MODE_REFLECT_X)
			cfg |= GSC_IN_ROT_XFLIP;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg |= GSC_IN_ROT_YFLIP;
		break;
	case DRM_MODE_ROTATE_90:
		cfg |= GSC_IN_ROT_90;
		if (rotation & DRM_MODE_REFLECT_X)
			cfg |= GSC_IN_ROT_XFLIP;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg |= GSC_IN_ROT_YFLIP;
		break;
	case DRM_MODE_ROTATE_180:
		cfg |= GSC_IN_ROT_180;
		if (rotation & DRM_MODE_REFLECT_X)
			cfg &= ~GSC_IN_ROT_XFLIP;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg &= ~GSC_IN_ROT_YFLIP;
		break;
	case DRM_MODE_ROTATE_270:
		cfg |= GSC_IN_ROT_270;
		if (rotation & DRM_MODE_REFLECT_X)
			cfg &= ~GSC_IN_ROT_XFLIP;
		if (rotation & DRM_MODE_REFLECT_Y)
			cfg &= ~GSC_IN_ROT_YFLIP;
		break;
	}

	gsc_write(cfg, GSC_IN_CON);

	ctx->rotation = (cfg & GSC_IN_ROT_90) ? 1 : 0;
}