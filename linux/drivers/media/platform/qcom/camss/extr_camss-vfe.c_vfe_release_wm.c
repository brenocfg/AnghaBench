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
struct vfe_device {int /*<<< orphan*/ * wm_output_map; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  VFE_LINE_NONE ; 

__attribute__((used)) static int vfe_release_wm(struct vfe_device *vfe, u8 wm)
{
	if (wm >= ARRAY_SIZE(vfe->wm_output_map))
		return -EINVAL;

	vfe->wm_output_map[wm] = VFE_LINE_NONE;

	return 0;
}