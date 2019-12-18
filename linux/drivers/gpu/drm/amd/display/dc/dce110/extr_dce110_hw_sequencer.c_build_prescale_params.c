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
struct ipp_prescale_params {int scale; int /*<<< orphan*/  mode; } ;
struct dc_plane_state {int format; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  IPP_PRESCALE_MODE_FIXED_UNSIGNED ; 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 132 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 131 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 130 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 129 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 128 

__attribute__((used)) static void build_prescale_params(struct ipp_prescale_params *prescale_params,
		const struct dc_plane_state *plane_state)
{
	prescale_params->mode = IPP_PRESCALE_MODE_FIXED_UNSIGNED;

	switch (plane_state->format) {
	case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		prescale_params->scale = 0x2082;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		prescale_params->scale = 0x2020;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		prescale_params->scale = 0x2008;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		prescale_params->scale = 0x2000;
		break;
	default:
		ASSERT(false);
		break;
	}
}