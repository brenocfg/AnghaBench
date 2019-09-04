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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDP_COLOR_420_MT21 ; 
 int /*<<< orphan*/  MDP_COLOR_I420 ; 
 int /*<<< orphan*/  MDP_COLOR_NV12 ; 
 int /*<<< orphan*/  MDP_COLOR_UNKNOWN ; 
 int /*<<< orphan*/  MDP_COLOR_YV12 ; 
#define  V4L2_PIX_FMT_MT21C 133 
#define  V4L2_PIX_FMT_NV12 132 
#define  V4L2_PIX_FMT_NV12M 131 
#define  V4L2_PIX_FMT_YUV420 130 
#define  V4L2_PIX_FMT_YUV420M 129 
#define  V4L2_PIX_FMT_YVU420 128 
 int /*<<< orphan*/  mtk_mdp_err (char*,int) ; 

__attribute__((used)) static int32_t mtk_mdp_map_color_format(int v4l2_format)
{
	switch (v4l2_format) {
	case V4L2_PIX_FMT_NV12M:
	case V4L2_PIX_FMT_NV12:
		return MDP_COLOR_NV12;
	case V4L2_PIX_FMT_MT21C:
		return MDP_COLOR_420_MT21;
	case V4L2_PIX_FMT_YUV420M:
	case V4L2_PIX_FMT_YUV420:
		return MDP_COLOR_I420;
	case V4L2_PIX_FMT_YVU420:
		return MDP_COLOR_YV12;
	}

	mtk_mdp_err("Unknown format 0x%x", v4l2_format);

	return MDP_COLOR_UNKNOWN;
}