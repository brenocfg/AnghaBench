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
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct file {struct bttv_fh* private_data; } ;
struct bttv_fh {size_t type; TYPE_2__* btv; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;
struct TYPE_4__ {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_queue (struct bttv_fh*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * v4l2_type_names ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int
bttv_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct bttv_fh *fh = file->private_data;

	dprintk("%d: mmap type=%s 0x%lx+%ld\n",
		fh->btv->c.nr, v4l2_type_names[fh->type],
		vma->vm_start, vma->vm_end - vma->vm_start);
	return videobuf_mmap_mapper(bttv_queue(fh),vma);
}