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
struct hantro_func {int /*<<< orphan*/  vdev; } ;
struct hantro_dev {struct hantro_func* decoder; struct hantro_func* encoder; } ;

/* Variables and functions */
 unsigned int MEDIA_ENT_F_PROC_VIDEO_ENCODER ; 
 int /*<<< orphan*/  hantro_detach_func (struct hantro_func*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hantro_remove_func(struct hantro_dev *vpu,
			       unsigned int funcid)
{
	struct hantro_func *func;

	if (funcid == MEDIA_ENT_F_PROC_VIDEO_ENCODER)
		func = vpu->encoder;
	else
		func = vpu->decoder;

	if (!func)
		return;

	hantro_detach_func(func);
	video_unregister_device(&func->vdev);
}