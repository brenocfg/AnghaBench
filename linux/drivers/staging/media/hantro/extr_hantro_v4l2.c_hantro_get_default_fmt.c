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
struct hantro_fmt {scalar_t__ codec_mode; } ;

/* Variables and functions */
 scalar_t__ HANTRO_MODE_NONE ; 

__attribute__((used)) static const struct hantro_fmt *
hantro_get_default_fmt(const struct hantro_fmt *formats, unsigned int num_fmts,
		       bool bitstream)
{
	unsigned int i;

	for (i = 0; i < num_fmts; i++) {
		if (bitstream == (formats[i].codec_mode !=
				  HANTRO_MODE_NONE))
			return &formats[i];
	}
	return NULL;
}