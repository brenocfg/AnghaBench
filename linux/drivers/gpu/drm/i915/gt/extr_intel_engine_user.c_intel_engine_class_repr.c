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
typedef  size_t u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 
#define  COPY_ENGINE_CLASS 131 
#define  RENDER_CLASS 130 
#define  VIDEO_DECODE_CLASS 129 
#define  VIDEO_ENHANCEMENT_CLASS 128 

const char *intel_engine_class_repr(u8 class)
{
	static const char * const uabi_names[] = {
		[RENDER_CLASS] = "rcs",
		[COPY_ENGINE_CLASS] = "bcs",
		[VIDEO_DECODE_CLASS] = "vcs",
		[VIDEO_ENHANCEMENT_CLASS] = "vecs",
	};

	if (class >= ARRAY_SIZE(uabi_names) || !uabi_names[class])
		return "xxx";

	return uabi_names[class];
}