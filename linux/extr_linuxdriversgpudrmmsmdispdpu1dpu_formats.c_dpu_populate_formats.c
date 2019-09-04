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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
struct dpu_format_extended {size_t fourcc_format; int /*<<< orphan*/  modifier; } ;

/* Variables and functions */

uint32_t dpu_populate_formats(
		const struct dpu_format_extended *format_list,
		uint32_t *pixel_formats,
		uint64_t *pixel_modifiers,
		uint32_t pixel_formats_max)
{
	uint32_t i, fourcc_format;

	if (!format_list || !pixel_formats)
		return 0;

	for (i = 0, fourcc_format = 0;
			format_list->fourcc_format && i < pixel_formats_max;
			++format_list) {
		/* verify if listed format is in dpu_format_map? */

		/* optionally return modified formats */
		if (pixel_modifiers) {
			/* assume same modifier for all fb planes */
			pixel_formats[i] = format_list->fourcc_format;
			pixel_modifiers[i++] = format_list->modifier;
		} else {
			/* assume base formats grouped together */
			if (fourcc_format != format_list->fourcc_format) {
				fourcc_format = format_list->fourcc_format;
				pixel_formats[i++] = fourcc_format;
			}
		}
	}

	return i;
}