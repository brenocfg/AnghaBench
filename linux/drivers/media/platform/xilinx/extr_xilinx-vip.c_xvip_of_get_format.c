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
struct xvip_video_format {unsigned int vf_code; scalar_t__ width; int /*<<< orphan*/  pattern; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct xvip_video_format*) ; 
 int EINVAL ; 
 struct xvip_video_format const* ERR_PTR (int) ; 
 unsigned int XVIP_VF_MONO_SENSOR ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,...) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct xvip_video_format* xvip_video_formats ; 

const struct xvip_video_format *xvip_of_get_format(struct device_node *node)
{
	const char *pattern = "mono";
	unsigned int vf_code;
	unsigned int i;
	u32 width;
	int ret;

	ret = of_property_read_u32(node, "xlnx,video-format", &vf_code);
	if (ret < 0)
		return ERR_PTR(ret);

	ret = of_property_read_u32(node, "xlnx,video-width", &width);
	if (ret < 0)
		return ERR_PTR(ret);

	if (vf_code == XVIP_VF_MONO_SENSOR)
		of_property_read_string(node, "xlnx,cfa-pattern", &pattern);

	for (i = 0; i < ARRAY_SIZE(xvip_video_formats); ++i) {
		const struct xvip_video_format *format = &xvip_video_formats[i];

		if (format->vf_code != vf_code || format->width != width)
			continue;

		if (vf_code == XVIP_VF_MONO_SENSOR &&
		    strcmp(pattern, format->pattern))
			continue;

		return format;
	}

	return ERR_PTR(-EINVAL);
}