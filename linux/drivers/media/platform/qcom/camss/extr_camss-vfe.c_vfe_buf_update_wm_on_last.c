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
struct vfe_output {int state; } ;
struct vfe_device {TYPE_1__* camss; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  VFE_OUTPUT_CONTINUOUS 129 
#define  VFE_OUTPUT_SINGLE 128 
 int VFE_OUTPUT_STOPPING ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vfe_output_frame_drop (struct vfe_device*,struct vfe_output*,int) ; 

__attribute__((used)) static void vfe_buf_update_wm_on_last(struct vfe_device *vfe,
				      struct vfe_output *output)
{
	switch (output->state) {
	case VFE_OUTPUT_CONTINUOUS:
		output->state = VFE_OUTPUT_SINGLE;
		vfe_output_frame_drop(vfe, output, 1);
		break;
	case VFE_OUTPUT_SINGLE:
		output->state = VFE_OUTPUT_STOPPING;
		vfe_output_frame_drop(vfe, output, 0);
		break;
	default:
		dev_err_ratelimited(vfe->camss->dev,
				    "Last buff in wrong state! %d\n",
				    output->state);
		break;
	}
}