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
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EM28XX_RESOURCE_VBI ; 
 int EM28XX_RESOURCE_VIDEO ; 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int get_resource(enum v4l2_buf_type f_type)
{
	switch (f_type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		return EM28XX_RESOURCE_VIDEO;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
		return EM28XX_RESOURCE_VBI;
	default:
		WARN_ON(1);
		return -1; /* Indicate that device is busy */
	}
}