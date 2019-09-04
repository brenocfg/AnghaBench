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
struct venus_inst {int dummy; } ;
struct venus_format {scalar_t__ type; int /*<<< orphan*/  pixfmt; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct venus_format*) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 struct venus_format* venc_formats ; 
 scalar_t__ venus_helper_check_codec (struct venus_inst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct venus_format *
find_format_by_index(struct venus_inst *inst, unsigned int index, u32 type)
{
	const struct venus_format *fmt = venc_formats;
	unsigned int size = ARRAY_SIZE(venc_formats);
	unsigned int i, k = 0;

	if (index > size)
		return NULL;

	for (i = 0; i < size; i++) {
		bool valid;

		if (fmt[i].type != type)
			continue;
		valid = type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ||
			venus_helper_check_codec(inst, fmt[i].pixfmt);
		if (k == index && valid)
			break;
		if (valid)
			k++;
	}

	if (i == size)
		return NULL;

	return &fmt[i];
}