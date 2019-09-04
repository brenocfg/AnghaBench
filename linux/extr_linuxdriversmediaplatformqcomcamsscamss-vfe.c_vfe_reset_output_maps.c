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
struct vfe_device {int /*<<< orphan*/ * wm_output_map; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VFE_LINE_NONE ; 

__attribute__((used)) static void vfe_reset_output_maps(struct vfe_device *vfe)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(vfe->wm_output_map); i++)
		vfe->wm_output_map[i] = VFE_LINE_NONE;
}