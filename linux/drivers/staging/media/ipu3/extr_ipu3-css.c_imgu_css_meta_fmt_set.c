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
struct v4l2_meta_format {int dataformat; int buffersize; } ;
struct ipu3_uapi_stats_3a {int dummy; } ;
struct ipu3_uapi_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_META_FMT_IPU3_PARAMS 129 
#define  V4L2_META_FMT_IPU3_STAT_3A 128 

int imgu_css_meta_fmt_set(struct v4l2_meta_format *fmt)
{
	switch (fmt->dataformat) {
	case V4L2_META_FMT_IPU3_PARAMS:
		fmt->buffersize = sizeof(struct ipu3_uapi_params);
		break;
	case V4L2_META_FMT_IPU3_STAT_3A:
		fmt->buffersize = sizeof(struct ipu3_uapi_stats_3a);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}