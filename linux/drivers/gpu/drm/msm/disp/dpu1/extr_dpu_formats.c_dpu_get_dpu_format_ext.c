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
typedef  int uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_2__ {size_t const pixel_format; } ;
struct dpu_format {TYPE_1__ base; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct dpu_format*) ; 
 int /*<<< orphan*/  DPU_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  DPU_FORMAT_IS_UBWC (struct dpu_format const*) ; 
 int /*<<< orphan*/  DPU_FORMAT_IS_YUV (struct dpu_format const*) ; 
#define  DRM_FORMAT_MOD_QCOM_COMPRESSED 128 
 struct dpu_format* dpu_format_map ; 
 struct dpu_format* dpu_format_map_ubwc ; 

const struct dpu_format *dpu_get_dpu_format_ext(
		const uint32_t format,
		const uint64_t modifier)
{
	uint32_t i = 0;
	const struct dpu_format *fmt = NULL;
	const struct dpu_format *map = NULL;
	ssize_t map_size = 0;

	/*
	 * Currently only support exactly zero or one modifier.
	 * All planes use the same modifier.
	 */
	DPU_DEBUG("plane format modifier 0x%llX\n", modifier);

	switch (modifier) {
	case 0:
		map = dpu_format_map;
		map_size = ARRAY_SIZE(dpu_format_map);
		break;
	case DRM_FORMAT_MOD_QCOM_COMPRESSED:
		map = dpu_format_map_ubwc;
		map_size = ARRAY_SIZE(dpu_format_map_ubwc);
		DPU_DEBUG("found fmt: %4.4s  DRM_FORMAT_MOD_QCOM_COMPRESSED\n",
				(char *)&format);
		break;
	default:
		DPU_ERROR("unsupported format modifier %llX\n", modifier);
		return NULL;
	}

	for (i = 0; i < map_size; i++) {
		if (format == map[i].base.pixel_format) {
			fmt = &map[i];
			break;
		}
	}

	if (fmt == NULL)
		DPU_ERROR("unsupported fmt: %4.4s modifier 0x%llX\n",
			(char *)&format, modifier);
	else
		DPU_DEBUG("fmt %4.4s mod 0x%llX ubwc %d yuv %d\n",
				(char *)&format, modifier,
				DPU_FORMAT_IS_UBWC(fmt),
				DPU_FORMAT_IS_YUV(fmt));

	return fmt;
}