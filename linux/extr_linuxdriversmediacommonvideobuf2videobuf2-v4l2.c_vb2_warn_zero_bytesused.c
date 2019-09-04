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
struct vb2_buffer {TYPE_1__* vb2_queue; } ;
struct TYPE_2__ {scalar_t__ allow_zero_bytesused; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static void vb2_warn_zero_bytesused(struct vb2_buffer *vb)
{
	static bool check_once;

	if (check_once)
		return;

	check_once = true;

	pr_warn("use of bytesused == 0 is deprecated and will be removed in the future,\n");
	if (vb->vb2_queue->allow_zero_bytesused)
		pr_warn("use VIDIOC_DECODER_CMD(V4L2_DEC_CMD_STOP) instead.\n");
	else
		pr_warn("use the actual size instead.\n");
}