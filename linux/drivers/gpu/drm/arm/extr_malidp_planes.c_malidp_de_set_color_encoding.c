#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct malidp_plane {TYPE_1__* layer; int /*<<< orphan*/  hwdev; } ;
typedef  enum drm_color_range { ____Placeholder_drm_color_range } drm_color_range ;
typedef  enum drm_color_encoding { ____Placeholder_drm_color_encoding } drm_color_encoding ;
struct TYPE_2__ {scalar_t__ yuv2rgb_offset; scalar_t__ base; } ;

/* Variables and functions */
 unsigned int MALIDP_COLORADJ_NUM_COEFFS ; 
 int /*<<< orphan*/  malidp_hw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ *** malidp_yuv2rgb_coeffs ; 

__attribute__((used)) static void malidp_de_set_color_encoding(struct malidp_plane *plane,
					 enum drm_color_encoding enc,
					 enum drm_color_range range)
{
	unsigned int i;

	for (i = 0; i < MALIDP_COLORADJ_NUM_COEFFS; i++) {
		/* coefficients are signed, two's complement values */
		malidp_hw_write(plane->hwdev, malidp_yuv2rgb_coeffs[enc][range][i],
				plane->layer->base + plane->layer->yuv2rgb_offset +
				i * 4);
	}
}