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
struct stm32_dcmi {unsigned int num_of_sd_formats; struct dcmi_format** sd_formats; } ;
struct dcmi_format {unsigned int fourcc; } ;

/* Variables and functions */

__attribute__((used)) static const struct dcmi_format *find_format_by_fourcc(struct stm32_dcmi *dcmi,
						       unsigned int fourcc)
{
	unsigned int num_formats = dcmi->num_of_sd_formats;
	const struct dcmi_format *fmt;
	unsigned int i;

	for (i = 0; i < num_formats; i++) {
		fmt = dcmi->sd_formats[i];
		if (fmt->fourcc == fourcc)
			return fmt;
	}

	return NULL;
}