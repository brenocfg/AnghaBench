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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int dce_virtual_crtc_get_scanoutpos(struct amdgpu_device *adev, int crtc,
					u32 *vbl, u32 *position)
{
	*vbl = 0;
	*position = 0;

	return -EINVAL;
}