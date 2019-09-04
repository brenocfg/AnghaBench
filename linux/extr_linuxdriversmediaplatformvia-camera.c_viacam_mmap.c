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
struct vm_area_struct {int dummy; } ;
struct via_camera {int /*<<< orphan*/  vb_queue; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct via_camera* video_drvdata (struct file*) ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ *,struct vm_area_struct*) ; 

__attribute__((used)) static int viacam_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct via_camera *cam = video_drvdata(filp);

	return videobuf_mmap_mapper(&cam->vb_queue, vma);
}