#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {TYPE_1__* df_funcs; } ;
struct TYPE_2__ {int (* get_fb_channel_number ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * df_v1_7_channel_number ; 
 int stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static u32 df_v1_7_get_hbm_channel_number(struct amdgpu_device *adev)
{
	int fb_channel_number;

	fb_channel_number = adev->df_funcs->get_fb_channel_number(adev);

	return df_v1_7_channel_number[fb_channel_number];
}