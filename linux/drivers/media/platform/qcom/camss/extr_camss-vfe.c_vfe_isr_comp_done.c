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
typedef  int /*<<< orphan*/  u8 ;
struct vfe_device {scalar_t__* wm_output_map; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ VFE_LINE_PIX ; 
 int /*<<< orphan*/  vfe_isr_wm_done (struct vfe_device*,unsigned int) ; 

__attribute__((used)) static void vfe_isr_comp_done(struct vfe_device *vfe, u8 comp)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(vfe->wm_output_map); i++)
		if (vfe->wm_output_map[i] == VFE_LINE_PIX) {
			vfe_isr_wm_done(vfe, i);
			break;
		}
}