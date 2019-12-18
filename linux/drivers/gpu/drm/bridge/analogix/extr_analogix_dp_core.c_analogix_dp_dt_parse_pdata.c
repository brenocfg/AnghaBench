#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_info {int max_link_rate; int max_lane_count; } ;
struct device_node {int dummy; } ;
struct analogix_dp_device {TYPE_2__* plat_data; struct video_info video_info; TYPE_1__* dev; } ;
struct TYPE_4__ {int dev_type; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
#define  EXYNOS_DP 130 
#define  RK3288_DP 129 
#define  RK3399_EDP 128 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int analogix_dp_dt_parse_pdata(struct analogix_dp_device *dp)
{
	struct device_node *dp_node = dp->dev->of_node;
	struct video_info *video_info = &dp->video_info;

	switch (dp->plat_data->dev_type) {
	case RK3288_DP:
	case RK3399_EDP:
		/*
		 * Like Rk3288 DisplayPort TRM indicate that "Main link
		 * containing 4 physical lanes of 2.7/1.62 Gbps/lane".
		 */
		video_info->max_link_rate = 0x0A;
		video_info->max_lane_count = 0x04;
		break;
	case EXYNOS_DP:
		/*
		 * NOTE: those property parseing code is used for
		 * providing backward compatibility for samsung platform.
		 */
		of_property_read_u32(dp_node, "samsung,link-rate",
				     &video_info->max_link_rate);
		of_property_read_u32(dp_node, "samsung,lane-count",
				     &video_info->max_lane_count);
		break;
	}

	return 0;
}