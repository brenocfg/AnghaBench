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
struct decon_context {int dummy; } ;

/* Variables and functions */
 int BLENDERQ_ALPHA0 ; 
 int BLENDERQ_ALPHA_A ; 
 int BLENDERQ_A_FUNC_F (int) ; 
 int BLENDERQ_B_FUNC_F (int) ; 
 int BLENDERQ_ONE ; 
 int BLENDERQ_ONE_MINUS_ALPHA_A ; 
 int /*<<< orphan*/  DECON_BLENDERQx (unsigned int) ; 
 unsigned int DRM_BLEND_ALPHA_OPAQUE ; 
#define  DRM_MODE_BLEND_COVERAGE 130 
#define  DRM_MODE_BLEND_PIXEL_NONE 129 
#define  DRM_MODE_BLEND_PREMULTI 128 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void decon_win_set_bldeq(struct decon_context *ctx, unsigned int win,
				unsigned int alpha, unsigned int pixel_alpha)
{
	u32 mask = BLENDERQ_A_FUNC_F(0xf) | BLENDERQ_B_FUNC_F(0xf);
	u32 val = 0;

	switch (pixel_alpha) {
	case DRM_MODE_BLEND_PIXEL_NONE:
	case DRM_MODE_BLEND_COVERAGE:
		val |= BLENDERQ_A_FUNC_F(BLENDERQ_ALPHA_A);
		val |= BLENDERQ_B_FUNC_F(BLENDERQ_ONE_MINUS_ALPHA_A);
		break;
	case DRM_MODE_BLEND_PREMULTI:
	default:
		if (alpha != DRM_BLEND_ALPHA_OPAQUE) {
			val |= BLENDERQ_A_FUNC_F(BLENDERQ_ALPHA0);
			val |= BLENDERQ_B_FUNC_F(BLENDERQ_ONE_MINUS_ALPHA_A);
		} else {
			val |= BLENDERQ_A_FUNC_F(BLENDERQ_ONE);
			val |= BLENDERQ_B_FUNC_F(BLENDERQ_ONE_MINUS_ALPHA_A);
		}
		break;
	}
	decon_set_bits(ctx, DECON_BLENDERQx(win), mask, val);
}