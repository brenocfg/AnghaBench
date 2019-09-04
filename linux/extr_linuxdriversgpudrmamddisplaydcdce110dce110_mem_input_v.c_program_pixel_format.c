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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct dce_mem_input {TYPE_1__ base; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_DEPTH ; 
 int /*<<< orphan*/  GRPH_FORMAT ; 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 139 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 132 
#define  SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS 131 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 130 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr 129 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb 128 
 int SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 
 int /*<<< orphan*/  UNP_GRPH_CONTROL ; 
 int /*<<< orphan*/  UNP_GRPH_CONTROL_EXP ; 
 int /*<<< orphan*/  VIDEO_FORMAT ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUNP_GRPH_CONTROL ; 
 int /*<<< orphan*/  mmUNP_GRPH_CONTROL_EXP ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_pixel_format(
	struct dce_mem_input *mem_input110,
	enum surface_pixel_format format)
{
	if (format < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) {
		uint32_t value;
		uint8_t grph_depth;
		uint8_t grph_format;

		value =	dm_read_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL);

		switch (format) {
		case SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
			grph_depth = 0;
			grph_format = 0;
			break;
		case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
			grph_depth = 1;
			grph_format = 1;
			break;
		case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
		case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
			grph_depth = 2;
			grph_format = 0;
			break;
		case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
		case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
			grph_depth = 2;
			grph_format = 1;
			break;
		case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
			grph_depth = 3;
			grph_format = 0;
			break;
		default:
			grph_depth = 2;
			grph_format = 0;
			break;
		}

		set_reg_field_value(
				value,
				grph_depth,
				UNP_GRPH_CONTROL,
				GRPH_DEPTH);
		set_reg_field_value(
				value,
				grph_format,
				UNP_GRPH_CONTROL,
				GRPH_FORMAT);

		dm_write_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL,
				value);

		value =	dm_read_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL_EXP);

		/* VIDEO FORMAT 0 */
		set_reg_field_value(
				value,
				0,
				UNP_GRPH_CONTROL_EXP,
				VIDEO_FORMAT);
		dm_write_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL_EXP,
				value);

	} else {
		/* Video 422 and 420 needs UNP_GRPH_CONTROL_EXP programmed */
		uint32_t value;
		uint8_t video_format;

		value =	dm_read_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL_EXP);

		switch (format) {
		case SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
			video_format = 2;
			break;
		case SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
			video_format = 3;
			break;
		default:
			video_format = 0;
			break;
		}

		set_reg_field_value(
			value,
			video_format,
			UNP_GRPH_CONTROL_EXP,
			VIDEO_FORMAT);

		dm_write_reg(
			mem_input110->base.ctx,
			mmUNP_GRPH_CONTROL_EXP,
			value);
	}
}