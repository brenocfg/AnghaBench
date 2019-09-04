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
typedef  scalar_t__ u32 ;
struct jpu_fmt {scalar_t__ fourcc; unsigned int types; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct jpu_fmt*) ; 
 unsigned int JPU_DEC_CAPTURE ; 
 unsigned int JPU_DEC_OUTPUT ; 
 unsigned int JPU_ENC_CAPTURE ; 
 unsigned int JPU_ENC_OUTPUT ; 
 unsigned int JPU_FMT_TYPE_OUTPUT ; 
 struct jpu_fmt* jpu_formats ; 

__attribute__((used)) static struct jpu_fmt *jpu_find_format(bool encoder, u32 pixelformat,
				       unsigned int fmt_type)
{
	unsigned int i, fmt_flag;

	if (encoder)
		fmt_flag = fmt_type == JPU_FMT_TYPE_OUTPUT ? JPU_ENC_OUTPUT :
							     JPU_ENC_CAPTURE;
	else
		fmt_flag = fmt_type == JPU_FMT_TYPE_OUTPUT ? JPU_DEC_OUTPUT :
							     JPU_DEC_CAPTURE;

	for (i = 0; i < ARRAY_SIZE(jpu_formats); i++) {
		struct jpu_fmt *fmt = &jpu_formats[i];

		if (fmt->fourcc == pixelformat && fmt->types & fmt_flag)
			return fmt;
	}

	return NULL;
}