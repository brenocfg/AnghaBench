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
struct v4l2_pix_format {int width; int height; } ;
struct stm32_dcmi {unsigned int num_of_sd_framesizes; struct dcmi_framesize* sd_framesizes; } ;
struct dcmi_framesize {int width; int height; } ;

/* Variables and functions */
 unsigned int UINT_MAX ; 

__attribute__((used)) static void __find_outer_frame_size(struct stm32_dcmi *dcmi,
				    struct v4l2_pix_format *pix,
				    struct dcmi_framesize *framesize)
{
	struct dcmi_framesize *match = NULL;
	unsigned int i;
	unsigned int min_err = UINT_MAX;

	for (i = 0; i < dcmi->num_of_sd_framesizes; i++) {
		struct dcmi_framesize *fsize = &dcmi->sd_framesizes[i];
		int w_err = (fsize->width - pix->width);
		int h_err = (fsize->height - pix->height);
		int err = w_err + h_err;

		if (w_err >= 0 && h_err >= 0 && err < min_err) {
			min_err = err;
			match = fsize;
		}
	}
	if (!match)
		match = &dcmi->sd_framesizes[0];

	*framesize = *match;
}